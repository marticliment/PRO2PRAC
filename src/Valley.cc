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
    assert(initialized && "The current Valley object is not initialized, but a method that requires it to be is being called.");
}

BinTree<string> Valley::GetRiverStructureFromStream(istream& stream)
{
    // Read city name and check if city is valid
    string city_name;
    stream >> city_name;
    if(city_name == "#") 
        return BinTree<string>();
     
    // Read city children
    BinTree<string> left, right;

    cities[city_name] = City(city_name);

    left = GetRiverStructureFromStream(stream);
    right = GetRiverStructureFromStream(stream);
    
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

bool Valley::HasCity(string id)
{
    AssertRiverArrayIsInitialized();
    return cities.find(id) != cities.end();
}

City& Valley::GetCity(string id)
{
    AssertRiverArrayIsInitialized();
    if(!HasCity(id))
        return invalid_city;

    return cities.at(id);
}

void Valley::DoTrades(BinTree<string> current_position)
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

void Valley::DisambiguateRoute(vector<NavigationDecision> current_route, BinTree<string> city, vector<vector<NavigationDecision>> &routes)
{
    if(city.empty())
    {
        routes.push_back(current_route);
    }
    else
    {
        auto& left_route = current_route;
        auto right_route = current_route;
        
        left_route.push_back(NavigationDecision::Left);
        right_route.push_back(NavigationDecision::Right);

        DisambiguateRoute(left_route, city.left(), routes);
        DisambiguateRoute(right_route, city.right(), routes);
    }
}

void print_route(const vector<NavigationDecision> &route)
{
    for(auto item: route)
            cout << NavigationDecisionAsString(item) << ',';
        cout << endl;
}

vector<vector<NavigationDecision>> Valley::GetRoutes()
{
    vector<vector<NavigationDecision>> routes;
    DisambiguateRoute(vector<NavigationDecision>(), river_structure, routes);
    return routes;
}

vector<NavigationDecision> Valley::GetBestRoute()
{
    auto routes = GetRoutes();
    int best_route_index = 0;
    int best_route_value = TestRoute(routes[0]);
    for(int i = 1; i < routes.size(); i++)
    {
        int route_value = TestRoute(routes[i]);
        if(route_value > best_route_value || (route_value == best_route_value && routes[i].size() < routes[best_route_index].size()))
        {                                                                 // TODO: perhaps add a <= here, but in theory not
            best_route_value = route_value;
            best_route_index = i;
        }
    }

    return routes[best_route_index];
}

int Valley::NavigateRoute(vector<NavigationDecision> &route, Ship &current_ship, bool dryrun)
{
    int route_position = 0;
    int total_traded = 0;
    BinTree<string> location = river_structure;
    string last_visited_city = "";

    Product current_buying_product = current_ship.BuyingProduct();
    Product current_selling_product = current_ship.SellingProduct();

    while(route_position < route.size() && !location.empty())
    {
        auto& city = GetCity(location.value());

        // Calculate how much product is going to be bought from the city
        int buying_id = current_buying_product.GetId();
        if(city.HasProduct(buying_id) && city.GetProduct(buying_id).ExceedingAmount() > 0)
        {
            int amount_to_buy = min(current_buying_product.MissingAmount(), city.GetProduct(buying_id).ExceedingAmount());
            current_buying_product.RestockAmount(amount_to_buy);
            if(!dryrun) // Only modify the city if we are not running on test mode
                city.GetProduct(buying_id).WithdrawAmount(amount_to_buy);
            total_traded += amount_to_buy;
        }

        // Calculate how much product is going to be sold to the city
        int selling_id = current_selling_product.GetId();
        if(city.HasProduct(selling_id) && city.GetProduct(selling_id).MissingAmount() > 0)
        {
            int amount_to_sell = min(current_selling_product.ExceedingAmount(), city.GetProduct(selling_id).MissingAmount());
            current_selling_product.WithdrawAmount(amount_to_sell);
            if(!dryrun) // Only modify the city if we are not running on test mode
                city.GetProduct(selling_id).RestockAmount(amount_to_sell);
            total_traded += amount_to_sell;
        }

        last_visited_city = location.value();

        if(current_selling_product.ExceedingAmount() == 0 && current_buying_product.MissingAmount())
        {
            // At this point there is nothing more to trade,
            // so the route will be corrected to end here
            while(route_position <= route.size())
                route.pop_back();
        }
        else
        {
            // Navigate to the next city
            if(route_position == route.size())
                route_position++;
            else if(route[route_position++] == NavigationDecision::Left)
                location = location.left();
            else
                location = location.right();
        }
    }

    if(total_traded != 0 && !dryrun)
        current_ship.AddVisitedCity(last_visited_city);

    return total_traded;
}

int Valley::TestRoute(vector<NavigationDecision> &route)
{
    Ship test_ship = GetShip().Copy();
    return NavigateRoute(route, test_ship, true);
}

int Valley::NavigateRoute(vector<NavigationDecision> route)
{
    return NavigateRoute(route, GetShip(), false);
}
