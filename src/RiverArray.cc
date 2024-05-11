#include "RiverArray.hh"

RiverArray::RiverArray()
{
    __initialized = false;
}

void RiverArray::__assert_river_array_is_initialized() const
{
    assert(__initialized && "The current RiverArray object is not initialized, but a method that requires it to be is being called.");
}

BinTree<City> RiverArray::__read_cities_from_stream(istream& reader)
{
    // Read city name and check if city is valid
    string city_name;
    reader >> city_name;
    if(city_name == "#") 
        return BinTree<City>();
     
    // Read city children
    BinTree<City> left, right;
    left = __read_cities_from_stream(reader);
    right = __read_cities_from_stream(reader);
    
    return BinTree<City>(City(city_name), left, right);
}

void RiverArray::InitializeFromStream(istream& reader)
{
    // Read the products
    int product_amount;
    reader >> product_amount;
    __product_data.resize(product_amount);
    for(int i = 0; i < product_amount; i++)
    {
        int weight, volume;
        cin >> weight >> volume;
        __product_data[i] = ProductData(weight, volume);
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