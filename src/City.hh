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
        int __weight;
        int __volume;

    public:
        City();
        City(string id);
        string GetId() const;
        void ReadFromStream(istream& stream);
        vector<int> GetProductIds() const;
        const Product& GetProduct(int id) const;
        bool HasProduct(int id) const;
        void AddProduct(Product p);
        int GetWeight() const;
        int GetVolume() const;
};

#endif