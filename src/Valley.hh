#ifndef RIVER_ARRAY_HH
#define RIVER_ARRAY_HH


#include <vector>
#include "NavigationDecisions.hh"
#include "lib/BinTree.hh"
#include "City.hh"
#include "Ship.hh"
#include "ProductData.hh"


class Valley
{
    private:
        static bool initialized;
        // There are methods where a city must be returned, but the 
        // wanted city does not exist. This city will be returned instead.
        static City invalid_city;
        static BinTree<string> river_structure;
        static map<string, City> cities;
        static Ship ship;

        static void AssertRiverArrayIsInitialized();
        static BinTree<string> GetRiverStructureFromStream(istream& stream);
        
        static void DoTrades(BinTree<string> current_position);
        
        static void DisambiguateRoute(vector<NavigationDecision> current_route, BinTree<string> city, vector<vector<NavigationDecision>> &routes);
        static int TestRoute(vector<NavigationDecision> route);

    public:
        static void InitializeFromStream(istream& stream);
        static void ReadCitiesFromStream(istream& stream);
        static Ship& GetShip();
        
        static vector<string> GetCities();
        static City& GetCity(string id);
        static bool HasCity(string id);
        
        static void DoTrades();
        
        static vector<vector<NavigationDecision>> GetRoutes();
        static vector<NavigationDecision> GetBestRoute();
        static int NavigateRoute(vector<NavigationDecision> route);
};


#endif