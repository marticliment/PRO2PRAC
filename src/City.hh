#ifndef CITY_HH
#define CITY_HH

#include <map>
#include <iostream>
#include "Product.hh"

using namespace std;

class City
{
    private:
        string __id;
        map<int, Product> __inventory;

    public:
        City();
        City(string id);
        string GetId() const;
        void ReadFromStream(istream& stream);
        vector<int> GetProductIds() const;
        Product& GetProduct(int id);
        bool HasProduct(int id) const;
        void AddProduct(Product p);
        void UpdateProduct(Product p);
        void RemoveProduct(int product_id);
        int GetWeight() const;
        int GetVolume() const;
        void Trade(City& other);
};

#endif