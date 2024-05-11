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