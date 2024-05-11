#include "Ship.hh"

Ship::Ship()
{
    Ship(Product(), Product());
}

Ship::Ship(Product buying, Product selling)
{
    __buying_product = buying;
    __selling_product = selling;
}

Product& Ship::BuyingProduct()
{
    return __buying_product;
}

Product& Ship::SellingProduct()
{
    return __selling_product;
}

void Ship::ReadFromStream(istream& stream)
{
    int buy_id, buy_amount, sell_id, sell_amount;
    stream >> buy_id >> buy_amount >> sell_id >> sell_amount;
    __buying_product = Product(buy_id, 0, buy_amount);
    __selling_product = Product(sell_id, sell_amount, 0);
}