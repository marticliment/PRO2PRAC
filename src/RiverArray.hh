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
        bool __initialized;
        
        BinTree<City> __river_structure;
        vector<ProductData> __product_data;
        Ship __ship;

        void __assert_river_array_is_initialized() const;
        static BinTree<City> __read_cities_from_stream(istream& reader);

    public:
        RiverArray();
        void InitializeFromStream(istream& reader);
        Ship& GetShip();
};


#endif