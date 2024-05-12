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
    //TODO: Reset ship voyages??
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

vector<vector<NavigationDecision>> Valley::GetRoutes()
{
    vector<vector<NavigationDecision>> routes;
    DisambiguateRoute(vector<NavigationDecision>(), river_structure, routes);
    return routes;
}

int Valley::TestRoute(vector<NavigationDecision> route)
{
    route.clear();
    return 0;
}

vector<NavigationDecision> Valley::GetBestRoute()
{
    auto routes = GetRoutes();
    return routes[0];
}

int Valley::NavigateRoute(vector<NavigationDecision> route)
{
    route.clear();
    return -1;
}
