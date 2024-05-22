#include <set>
#include <unordered_map>
#include "ProductReference.hh"
#include "Valley.hh"
#include "debug.hh"

using namespace std;


bool Valley::initialized = false;
City Valley::invalid_city = City("invalid");
BinTree<string> Valley::river_structure = BinTree<string>();
unordered_map<string, City> Valley::cities = unordered_map<string, City>();
Ship Valley::ship = Ship();

void Valley::AssertRiverArrayIsInitialized()
{
    assert(initialized && (true || "The current Valley object is not initialized, but a method that requires it to be is being called."));
}

BinTree<string> Valley::GetRiverNodeFromStream(istream& stream)
{
    // Read city name and check if city is valid
    string city_name;
    stream >> city_name;
    if(city_name == "#") 
        return BinTree<string>();
    
    cities.emplace(city_name, City(city_name));

    BinTree<string> left = GetRiverNodeFromStream(stream);
    BinTree<string> right = GetRiverNodeFromStream(stream);
    
    return BinTree<string>(city_name, left, right);
}

void Valley::ReadCitiesFromStream(istream& stream)
{
    cities.clear();
    river_structure = GetRiverNodeFromStream(stream);
    ship.ResetVisitedCities();
}

void Valley::InitializeFromStream(istream& stream)
{
    int count;
    stream >> count;
    ProductReference::AddFromStream(stream, count);
    ReadCitiesFromStream(stream);
    ship.ReadFromStream(stream);
    initialized = true;
}

Ship& Valley::GetShip()
{
    AssertRiverArrayIsInitialized();
    return ship;
}

vector<string> Valley::GetCityIds()
{
    AssertRiverArrayIsInitialized();
    vector<string> names;
    auto it = cities.begin();
    while(it != cities.end())
    {
        names.push_back(it->first);
        it++;
    }
    return names;
}

bool Valley::HasCity(const string& id)
{
    AssertRiverArrayIsInitialized();
    return cities.find(id) != cities.end();
}

City& Valley::GetCity(const string& id)
{
    AssertRiverArrayIsInitialized();
    if(!HasCity(id))
        return invalid_city;

    return cities.at(id);
}

void Valley::DoTrades(const BinTree<string> &current_position)
{
    AssertRiverArrayIsInitialized();

    if(current_position.empty())
        return;

    auto& current_city = GetCity(current_position.value());
    
    if(!current_position.left().empty())
    {
        current_city.TradeWith(GetCity(current_position.left().value()));
        DoTrades(current_position.left());
    }

    if(!current_position.right().empty())
    {
        current_city.TradeWith(GetCity(current_position.right().value()));
        DoTrades(current_position.right());
    }
}

void Valley::DoTrades()
{
    AssertRiverArrayIsInitialized();
    DoTrades(river_structure);
}

void Valley::TestRouteStep(vector<NavStep>& current_route, 
        const BinTree<string>& current_location, 
        int bought_amount,
        int sold_amount,
        int recently_skipped_cities,
        Ship& test_ship,
        Valley::RouteEvaluationResult &best_route)
{
    int buying_id = test_ship.BuyingProduct().GetId();
    int selling_id = test_ship.SellingProduct().GetId();
    
    int traded_amount = 0;
    auto& city = GetCity(current_location.value());

    // Calculate how much product is going to be bought from the city
    if(city.HasProduct(buying_id))
    {   
        int amount_to_buy = min(city.GetProductExceedingAmount(buying_id), test_ship.BuyingProduct().GetMissingAmount());
        test_ship.BuyingProduct().RestockAmount(amount_to_buy); 
        traded_amount += amount_to_buy;
        bought_amount += amount_to_buy;
    }

    // Calculate how much product is going to be sold to the city
    if(city.HasProduct(selling_id))
    {
        int amount_to_sell = min(city.GetProductMissingAmount(selling_id), test_ship.SellingProduct().GetExceedingAmount());
        test_ship.SellingProduct().WithdrawAmount(amount_to_sell);
        traded_amount += amount_to_sell;
        sold_amount += amount_to_sell;
    }

    // If the current city has tradable product, reset the skipped cities counter
    // Otherwhise, increase it
    if(traded_amount > 0)
        recently_skipped_cities = 0;
    else
        recently_skipped_cities++;
    
    // If we have reached the end of the river 
    // or if we have reached the limits of the ship's trading capacity
    if((current_location.right().empty() && current_location.left().empty())
        || (test_ship.BuyingProduct().GetMissingAmount() == 0 
        && test_ship.SellingProduct().GetExceedingAmount() == 0))
    {
        while(recently_skipped_cities > 0 && !current_route.empty())
        {
            // If the first city has been skipped, since the first city does not 
            // have an asscoiated NavStep on current_route, attempting to pop_back() would crash
            current_route.pop_back();
            recently_skipped_cities--;
        }

        Valley::RouteEvaluationResult result;
        result.route = current_route;
        // We need to add 1 to take into account the first city, which does not 
        // have associated any NavStep on current_route
        result.EffectiveLength = current_route.size() + 1 - recently_skipped_cities;
        result.TotalTrades = bought_amount + sold_amount;

        if(result.TotalTrades > best_route.TotalTrades
            || (result.TotalTrades == best_route.TotalTrades 
            && result.EffectiveLength < best_route.EffectiveLength))
        {
            best_route = result;
        }
    }
    else
    {
        // Continue testing through the left
        auto left_route = current_route;
        auto left_ship = test_ship.Copy();
        left_route.push_back(Valley::NavStep::Left);
        TestRouteStep(left_route, current_location.left(), bought_amount, sold_amount, recently_skipped_cities, left_ship, best_route);
        
        // Continue testing through the right
        current_route.push_back(Valley::NavStep::Right);
        TestRouteStep(current_route, current_location.right(), bought_amount, sold_amount, recently_skipped_cities, test_ship, best_route);
    }
}

vector<Valley::NavStep> Valley::GetBestRoute()
{
    Valley::RouteEvaluationResult best_route;
    vector<Valley::NavStep> empty_route;
    best_route.route = empty_route;
    auto test_ship = ship.Copy();
    TestRouteStep(empty_route, river_structure, 0, 0, 0, test_ship, best_route);
    return best_route.route;
}


int Valley::NavigateRoute(const vector<Valley::NavStep>& route_)
{
    auto route = route_;
    int route_position = 0;
    int total_traded = 0;
    BinTree<string> location = river_structure;
    string last_traded_city = "";

    Product current_buying_product = ship.BuyingProduct();
    Product current_selling_product = ship.SellingProduct();

    while(route_position <= route.size())
    {
        auto& city = GetCity(location.value());
        int city_traded = 0;

        // Calculate how much product is going to be bought from the city
        int buying_id = current_buying_product.GetId();
        if(city.HasProduct(buying_id) && city.GetProductExceedingAmount(buying_id) > 0)
        {
            int amount_to_buy = min(
                current_buying_product.GetMissingAmount(),
                city.GetProductExceedingAmount(buying_id)
            );
            current_buying_product.RestockAmount(amount_to_buy);
            city.WithdrawProductAmount(buying_id, amount_to_buy);
            city_traded += amount_to_buy;
        }

        // Calculate how much product is going to be sold to the city
        int selling_id = current_selling_product.GetId();
        if(city.HasProduct(selling_id) && city.GetProductMissingAmount(selling_id) > 0)
        {
            int amount_to_sell = min(
                current_selling_product.GetExceedingAmount(), 
                city.GetProductMissingAmount(selling_id)
            );
            current_selling_product.WithdrawAmount(amount_to_sell);
            city.RestockProductAmount(selling_id, amount_to_sell);
            city_traded += amount_to_sell;
        }

        total_traded += city_traded;
        // Only count a city as traded with when it has actually traded things
        if(city_traded > 0)
            last_traded_city = location.value();

        
        // If this is the last city, do not try to unpack the next position from route
        if(route_position == route.size())
            route_position++;
        // Otherwise, navigate to the next position
        else if(route[route_position++] == Valley::NavStep::Left)
            location = location.left();
        else
            location = location.right();
    }

    if(total_traded > 0)
        ship.AddVisitedCity(last_traded_city);

    return total_traded;
}
