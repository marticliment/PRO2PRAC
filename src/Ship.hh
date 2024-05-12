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
        string last_visted_city = "";

    public:
        Ship();
        Ship(Product buying, Product selling);
        Product& BuyingProduct();
        Product& SellingProduct();
        string GetLastVisitedCity() const;
        void SetLastVisitedCity(string city);
        void ReadFromStream(istream& stream);
        Ship Copy() const;

};

#endif