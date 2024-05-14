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
        vector<string> visited_cities;

    public:
        Ship();
        Ship(Product buying, Product selling);
        Product& BuyingProduct();
        Product& SellingProduct();
        const vector<string>& GetVisitedCities() const;
        void AddVisitedCity(const string& city);
        void ResetVisitedCities();
        void ReadFromStream(istream& stream);
        Ship Copy() const;

};

#endif