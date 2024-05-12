#ifndef RIVER_ARRAY_HH
#define RIVER_ARRAY_HH


#include <vector>
#include "NavigationDecisions.hh"
#include "lib/BinTree.hh"
#include "City.hh"
#include "Ship.hh"
#include "ProductData.hh"


class RiverArray
{
    private:
        bool __initialized = false;
        // There are methods where a city must be returned, but the 
        // wanted city does not exist. This city will be returned instead.
        City __invalid_city = City("invalid");
        
        BinTree<string> __river_structure;
        map<string, City> __cities;
        Ship __ship;

        void __assert_river_array_is_initialized() const;
        BinTree<string> __city_reader_helper(istream& stream);

    public:
        RiverArray();
        void InitializeFromStream(istream& stream);
        void ReadCitiesFromStream(istream& stream);
        Ship& GetShip();
        vector<string> GetCities() const;
        City& GetCity(string id);
        bool HasCity(string id) const;
};


#endif