#include "Ship.hh"
#include "ProductReference.hh"

Ship::Ship()
{
    Ship(Product(), Product());
}

Ship::Ship(Product buying, Product selling)
{
    buying_product = buying;
    selling_product = selling;
    last_visted_city = "";
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

string Ship::GetLastVisitedCity() const
{
    return last_visted_city;
}

void Ship::SetLastVisitedCity(string city)
{
    last_visted_city = city;
}

Ship Ship::Copy() const
{
    Product sold_product = Product(selling_product.GetId(), selling_product.GetCurrentAmount(), selling_product.GetWantedAmount());
    Product bougth_product = Product(buying_product.GetId(), buying_product.GetCurrentAmount(), buying_product.GetWantedAmount());
    Ship copy = Ship(bougth_product, sold_product);
    copy.SetLastVisitedCity(this->GetLastVisitedCity());
    return copy;
}