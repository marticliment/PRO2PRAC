#ifndef RIVER_ARRAY_HH
#define RIVER_ARRAY_HH


#include <vector>
#include "BinTree.hh"
#endif
#include "City.hh"
#include "Ship.hh"
#include "ProductData.hh"


class Valley
{
    public:
        enum class NavStep
        {
            Left,
            Right,
        };

    private:

        struct RouteResult
        {
            vector<Valley::NavStep> route;
            int EffectiveLength = 0;
            int TotalTrades = 0;
        };

        static bool initialized;
        // There are methods where a city must be returned, but the 
        // wanted city does not exist. This city will be returned instead.
        static City invalid_city;
        static BinTree<string> river_structure;
        static map<string, City> cities;
        static Ship ship;

        static void AssertRiverArrayIsInitialized();
        static BinTree<string> GetRiverStructureFromStream(istream& stream);
        
        static void DoTrades(const BinTree<string> &current_position);        
        static void TestRoutePiece(vector<NavStep>& current_route, const BinTree<string>& current_location, int buyable_amount, int sellable_amount, int skipped_cities, RouteResult &best_route);
    
    public:
        static void InitializeFromStream(istream& stream);
        static void ReadCitiesFromStream(istream& stream);
        static Ship& GetShip();
        
        static vector<string> GetCities();
        static City& GetCity(const string& id);
        static bool HasCity(const string& id);
        
        static void DoTrades();
        
        static vector<NavStep> GetBestRoute();
        static int NavigateRoute(const vector<NavStep>& route);
};

