#ifndef SHIP_HH
#define SHIP_HH


#include <vector>
#include "Product.hh"

using namespace std;

class Ship
{
    private:
        Product __buying_product;
        Product __selling_product;

    public:
        Ship();
        Ship(Product buying, Product selling);
        Product& BuyingProduct();
        Product& SellingProduct();

};

#endif