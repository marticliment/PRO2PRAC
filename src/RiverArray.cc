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

BinTree<string> RiverArray::__read_cities_from_stream(istream& reader)
{
    // Read city name and check if city is valid
    string city_name;
    reader >> city_name;
    if(city_name == "#") 
        return BinTree<string>();
     
    // Read city children
    BinTree<string> left, right;

    __cities[city_name] = City(city_name);

    left = __read_cities_from_stream(reader);
    right = __read_cities_from_stream(reader);
    
    return BinTree<string>(city_name, left, right);
}

void RiverArray::InitializeFromStream(istream& reader)
{
    // Read the products
    int product_amount;
    reader >> product_amount;
    for(int i = 0; i < product_amount; i++)
    {
        int weight, volume;
        cin >> weight >> volume;
        ProductReference::Add(ProductData(weight, volume));
    }

    // Read the cities
    __river_structure = __read_cities_from_stream(reader);

    // Read the ship
    int buy_id, buy_amount, sell_id, sell_amount;
    reader >> buy_id >> buy_amount >> sell_id >> sell_amount;
    __ship = Ship(Product(buy_id, 0, buy_amount), Product(sell_id, sell_amount, 0));

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
        names.push_back(it->first);
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