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
        bool initialized = false;
        // There are methods where a city must be returned, but the 
        // wanted city does not exist. This city will be returned instead.
        City invalid_city = City("invalid");
        
        BinTree<string> river_structure;
        map<string, City> cities;
        Ship ship;

        void AssertRiverArrayIsInitialized() const;
        BinTree<string> GetRiverStructureFromStream(istream& stream);
        void DoTrades(BinTree<string> current_position);

    public:
        RiverArray();
        void InitializeFromStream(istream& stream);
        void ReadCitiesFromStream(istream& stream);
        Ship& GetShip();
        vector<string> GetCities() const;
        City& GetCity(string id);
        bool HasCity(string id) const;
        void DoTrades();
};


#endif