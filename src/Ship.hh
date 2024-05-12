#ifndef SHIP_HH
#define SHIP_HH


#include <vector>
#include <iostream>
#include "Product.hh"

using namespace std;

class Ship
{
    private:
        Product buying_product;
        Product selling_product;

    public:
        Ship();
        Ship(Product buying, Product selling);
        Product& BuyingProduct();
        Product& SellingProduct();
        void ReadFromStream(istream& stream);

};

#endif