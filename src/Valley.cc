#include <set>
#include "ProductReference.hh"
#include "Valley.hh"
#include "debug.hh"

using namespace std;

bool Valley::initialized = false;
City Valley::invalid_city = City("invalid");
BinTree<string> Valley::river_structure = BinTree<string>();
map<string, City> Valley::cities = map<string, City>();
Ship Valley::ship = Ship();

void Valley::AssertRiverArrayIsInitialized()
{
    assert(initialized && (true || "The current Valley object is not initialized, but a method that requires it to be is being called."));
}

BinTree<string> Valley::GetRiverStructureFromStream(istream& stream)
{
    // Read city name and check if city is valid
    string city_name;
    stream >> city_name;
    if(city_name == "#") 
        return BinTree<string>();
    
    cities.emplace(city_name, City(city_name));

    BinTree<string> left = GetRiverStructureFromStream(stream);
    BinTree<string> right = GetRiverStructureFromStream(stream);
    
    return BinTree<string>(city_name, left, right);
}

void Valley::ReadCitiesFromStream(istream& stream)
{
    cities.clear();
    river_structure = GetRiverStructureFromStream(stream);
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

vector<string> Valley::GetCities()
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

void Valley::TestRoutePiece(vector<NavStep> current_route, const BinTree<string>& current_location, 
                            int buyable_amount, int sellable_amount, int skipped_cities,
                            Valley::RouteResult &best_route)
{
    int buying_id = ship.BuyingProduct().GetId();
    int selling_id = ship.SellingProduct().GetId();

    // If we have reached the end of the river 
    // or if we have reached the limits of the ship's trading capacity
    if(current_location.empty() || (ship.BuyingProduct().GetMissingAmount() <= buyable_amount && ship.SellingProduct().GetExceedingAmount() <= sellable_amount))
    {
        Valley::RouteResult result;
        result.route = current_route;
        result.EffectiveLength = current_route.size() - skipped_cities;
        result.TotalTrades = min(buyable_amount, ship.BuyingProduct().GetMissingAmount()) + 
            min(sellable_amount, ship.SellingProduct().GetExceedingAmount());
        // results.push_back(result);

        if(result.TotalTrades > best_route.TotalTrades || 
        (result.TotalTrades == best_route.TotalTrades && result.EffectiveLength < best_route.EffectiveLength))
            best_route = result;                        // TODO: perhaps add a <= here, but in theory not

        return;
    }
    
    // Calculate how much product is going to be bought from the city
    int traded_amount = 0;
    auto& city = GetCity(current_location.value());
    if(city.HasProduct(buying_id))
    {   
        int exceeding_amount = city.GetProductExceedingAmount(buying_id);
        traded_amount += exceeding_amount;
        buyable_amount += exceeding_amount;
    }

    // Calculate how much product is going to be sold to the city
    if(city.HasProduct(selling_id))
    {
        int missing_amount = city.GetProductMissingAmount(selling_id); 
        traded_amount += missing_amount;
        sellable_amount += missing_amount;
    }

    if(traded_amount == 0)
        skipped_cities++; 

    // Continue testing through the left
    current_route.push_back(NavStep::Left);
    TestRoutePiece(current_route, current_location.left(), buyable_amount, sellable_amount, skipped_cities, best_route);
    
    // Continue testing through the right
    current_route[current_route.size() - 1] = NavStep::Right;
    TestRoutePiece(current_route, current_location.right(), buyable_amount, sellable_amount, skipped_cities, best_route);
}

vector<Valley::NavStep> Valley::GetBestRoute()
{
    Valley::RouteResult best_route;
    TestRoutePiece(vector<Valley::NavStep>(), river_structure, 0, 0, 0, best_route);

    /*int best_index = 0;
    for(int i = 1; i < best_route.size(); i++)
    {
        if(best_route[i].TotalTrades > best_route[best_index].TotalTrades || 
        (best_route[i].TotalTrades == best_route[best_index].TotalTrades && best_route[i].EffectiveLength <= best_route[best_index].EffectiveLength))
            best_index = i;                                                                                                        // TODO: perhaps add a <= here, but in theory not
    }
    */
   return best_route.route;
}


int Valley::NavigateRoute(const vector<Valley::NavStep>& route)
{
    int route_position = 0;
    int total_traded = 0;
    BinTree<string> location = river_structure;
    string last_traded_city = "";

    Product current_buying_product = ship.BuyingProduct();
    Product current_selling_product = ship.SellingProduct();

    while(route_position < route.size())
    {
        auto& city = GetCity(location.value());
        int city_traded = 0;

        // Calculate how much product is going to be bought from the city
        int buying_id = current_buying_product.GetId();
        if(city.HasProduct(buying_id) && city.GetProductExceedingAmount(buying_id) > 0)
        {
            int amount_to_buy = min(current_buying_product.GetMissingAmount(), city.GetProductExceedingAmount(buying_id));
            current_buying_product.RestockAmount(amount_to_buy);
            city.WithdrawProductAmount(buying_id, amount_to_buy);
            city_traded += amount_to_buy;
        }

        // Calculate how much product is going to be sold to the city
        int selling_id = current_selling_product.GetId();
        if(city.HasProduct(selling_id) && city.GetProductMissingAmount(selling_id) > 0)
        {
            int amount_to_sell = min(current_selling_product.GetExceedingAmount(), city.GetProductMissingAmount(selling_id));
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

    if(last_traded_city != "")
        ship.AddVisitedCity(last_traded_city);

    return total_traded;
}
