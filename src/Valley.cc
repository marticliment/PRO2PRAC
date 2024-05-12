#include "ProductReference.hh"
#include "Valley.hh"
#include "debug.hh"


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