#include "ProductReference.hh"
#include "RiverArray.hh"
#include "debug.hh"

RiverArray::RiverArray()
{
    initialized = false;
}

void RiverArray::AssertRiverArrayIsInitialized() const
{
    assert(initialized && "The current RiverArray object is not initialized, but a method that requires it to be is being called.");
}

BinTree<string> RiverArray::GetRiverStructureFromStream(istream& stream)
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

void RiverArray::ReadCitiesFromStream(istream& stream)
{
    cities.clear();
    river_structure = GetRiverStructureFromStream(stream);
    //TODO: Reset ship voyages??
}

void RiverArray::InitializeFromStream(istream& stream)
{
    int count;
    stream >> count;
    ProductReference::AddFromStream(stream, count);
    ReadCitiesFromStream(stream);
    ship.ReadFromStream(stream);
    initialized = true;
}

Ship& RiverArray::GetShip()
{
    AssertRiverArrayIsInitialized();
    return ship;
}

vector<string> RiverArray::GetCities() const
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

bool RiverArray::HasCity(string id) const
{
    AssertRiverArrayIsInitialized();
    return cities.find(id) != cities.end();
}

City& RiverArray::GetCity(string id)
{
    AssertRiverArrayIsInitialized();
    if(!HasCity(id))
        return invalid_city;

    return cities.at(id);
}

void RiverArray::DoTrades(BinTree<string> current_position)
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

void RiverArray::DoTrades()
{
    AssertRiverArrayIsInitialized();

    DoTrades(river_structure);
}