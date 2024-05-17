#include "Ship.hh"
#include "ProductReference.hh"
#include "debug.hh"

Ship::Ship()
{
    Ship(Product(), Product());
}

Ship::Ship(Product buying, Product selling)
{
    buying_product = buying;
    selling_product = selling;
    visited_cities = vector<string>();
}

Product& Ship::BuyingProduct()
{
    return buying_product;
}

Product& Ship::SellingProduct()
{
    return selling_product;
}

void Ship::ReadFromStream(istream& stream)
{
    int buy_id, buy_amount, sell_id, sell_amount;
    stream >> buy_id >> buy_amount >> sell_id >> sell_amount;

    if(buy_id == sell_id)
    {
        cout << "error: no se puede comprar y vender el mismo producto" << endl;
        return;
    }
    else if(!ProductReference::Contains(sell_id) || !ProductReference::Contains(buy_id))
    {
        cout << "error: no existe el producto" << endl;
        return;
    }

    buying_product = Product(buy_id, 0, buy_amount);
    selling_product = Product(sell_id, sell_amount, 0);
}


void Ship::AddVisitedCity(const string& city)
{
    visited_cities.push_back(city);
}

const vector<string>& Ship::GetVisitedCities() const
{
    return visited_cities;
}

void Ship::ResetVisitedCities()
{
    visited_cities.clear();
}