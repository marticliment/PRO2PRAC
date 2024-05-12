#include "ProductReference.hh"
#include "RiverArray.hh"
#include "debug.hh"

RiverArray::RiverArray()
{
    __initialized = false;
}

void RiverArray::__assert_river_array_is_initialized() const
{
    assert(__initialized && "The current RiverArray object is not initialized, but a method that requires it to be is being called.");
}

BinTree<string> RiverArray::__city_reader_helper(istream& stream)
{
    // Read city name and check if city is valid
    string city_name;
    stream >> city_name;
    if(city_name == "#") 
        return BinTree<string>();
     
    // Read city children
    BinTree<string> left, right;

    __cities[city_name] = City(city_name);

    left = __city_reader_helper(stream);
    right = __city_reader_helper(stream);
    
    return BinTree<string>(city_name, left, right);
}

void RiverArray::ReadCitiesFromStream(istream& stream)
{
    __cities.clear();
    __river_structure = __city_reader_helper(stream);
    //TODO: Reset ship voyages
}

void RiverArray::InitializeFromStream(istream& stream)
{
    int count;
    stream >> count;
    ProductReference::AddFromStream(stream, count);
    ReadCitiesFromStream(stream);
    __ship.ReadFromStream(stream);
    __initialized = true;
}

Ship& RiverArray::GetShip()
{
    __assert_river_array_is_initialized();
    return __ship;
}

vector<string> RiverArray::GetCities() const
{
    __assert_river_array_is_initialized();
    vector<string> names;
    auto it = __cities.begin();
    while(it != __cities.end())
    {
        names.push_back(it->first);
        it++;
    }
    return names;
}

bool RiverArray::HasCity(string id) const
{
    __assert_river_array_is_initialized();
    return __cities.find(id) != __cities.end();
}

City& RiverArray::GetCity(string id)
{
    __assert_river_array_is_initialized();
    if(!HasCity(id))
        return __invalid_city;

    return __cities.at(id);
}