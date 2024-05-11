#ifndef CITY_HH
#define CITY_HH

#include <map>
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
};

#endif