#ifndef RIVER_ARRAY_HH
#define RIVER_ARRAY_HH

#include <vector>
#include <unordered_map>
#include <map>
#include "BinTree.hh"
#include "City.hh"
#include "Ship.hh"
#include "ProductData.hh"

/**
 * @brief Represents a valley with cities (City objects), and a Ship that navigates and trades between cities.
 * 
 * The cities are organized on a BinTree-like structure, where each city has either two or zero children. There is always a root city
 */
class Valley
{
public:
    /**
     * @brief The NavStep enum represents the navigation steps (left or right) the ship can take from a certain node, assuming the root node is at the top
     */
    enum class NavStep
    {
        Left, /**< Navigate to the left child assuming the root node is at the top. */
        Right /**< Navigate to the right child assuming the root node is at the top. */
    };

private:
    /**
     * @brief The RouteEvaluationResult struct represents the result of evaluating a possible route for the ship.
     */
    struct RouteEvaluationResult
    {
        vector<Valley::NavStep> route; /**< The route steps. */
        int EffectiveLength = 0; /**< The effective length of the route. */
        int TotalTrades = 0; /**< The total number of trades in the route. */
    };

    static bool initialized; /**< Flag indicating if the Valley is initialized. */
    static City invalid_city; /**< An invalid city used to perform read operations when an invalid city Id is provided through cin. */
public:
    static BinTree<string> river_structure; /**< The river structure containing the city IDs. */
private:
    static unordered_map<string, City> cities; /**< A map that links a given city id with its corresponding City object. */
    static Ship ship; /**< The ship. */

    /**
     * @brief Asserts that the river array is initialized.
     * 
     * @pre None
     * @post Will crash the program if the valley is not initialized.
     */
    static void AssertRiverArrayIsInitialized();

    /**
     * @brief Reads a river node and its children from an input stream.
     * 
     * @param stream An input stream.
     * 
     * @pre The input stream is open and valid.
     * @post The current node and its children are read and returned.
     * 
     * @return The river structure represented on a BinTree<string> object.
     */
    static BinTree<string> GetRiverNodeFromStream(istream& stream);

    /**
     * @brief Will make the city at the given node trade with its children. At their time, 
     * the children will trade with their respective children, and so on.
     * 
     * @param current_position A node in the river structure.
     * 
     * @pre The current position is valid.
     * @post Trades are performed recursively starting from the current node.
     */
    static void DoTrades(const BinTree<string> &current_position);

    /**
     * @brief Tests a route step and updates the best route if necessary.
     * 
     * @param current_route The already traveled steps. Must be a valid vector<Valley::NavStep> 
     * and coherent with current_location
     * @param current_location The current location in the river structure. Must be a non-empty BinTree<string> node, 
     * where the value of the node is the id of an existing city. Both children of the node may be either empty or valid.
     * @param buyable_amount The amount that can still be bought. Cannot be negative
     * @param sellable_amount The amount that can still be sold. Cannot be negative
     * @param recently_skipped_cities The amount of skipped cities since the last city where a tarde was performed. Cannot be negative
     * @param test_ship The ship to use to test a route. Must be a valid ship.
     * @param best_route A reference to a variable holding the best possible route.
     * 
     * @pre current_location is a non-empty node and is coherent with current_route, best_route and ship are 
     * valid references to valid instances of their respective types, and buyable_amount and sellable_amount are non_negative.
     * @post All the possible routes parting from the given current_location are tested and the best route is saved to current_route.
     */
    static void TestRouteStep(vector<NavStep>& current_route, 
        const BinTree<string>& current_location, 
        int buyable_amount, 
        int sellable_amount,
        int recently_skipped_cities,
        Ship& test_ship,
        RouteEvaluationResult &best_route
    );

public:
    /**
     * @brief Initializes the Valley from the input stream. This implies reading the 
     * products to be added to the ProductReference, the cities that of the Valley and the Ship
     * 
     * @param stream The input stream.
     * 
     * @pre The input stream is open and valid.
     * @post The Valley is initialized from the input stream.
     */
    static void InitializeFromStream(istream& stream);

    /**
     * @brief Reads the cities from the input stream, overwriting the old Valley contents, if any.
     * All the data regarding the cities from the old valley is lost.
     * 
     * @param stream The input stream.
     * 
     * @pre The input stream is open and valid.
     * @post The cities are read from the input stream. The old Valley is overwritten. The ship forgets the old travel routes, but maintains its attributes
     */
    static void ReadCitiesFromStream(istream& stream);

    /**
     * @brief Gets a reference to the ship.
     * 
     * @pre None.
     * @post A reference to the ship is returned.
     * 
     * @return A reference to the ship.
     */
    static Ship& GetShip();

    /**
     * @brief Gets the list of city Ids in the Valley.
     * 
     * @pre None.
     * @post The list of city Ids is returned.
     * 
     * @return The list of city Ids.
     */
    static vector<string> GetCityIds();

    /**
     * @brief Gets the city with the specified ID.
     * 
     * @param id The ID of the city.
     * 
     * @pre The city with the specified ID exists.
     * @post The city with the specified ID is returned.
     * 
     * @return The city with the specified ID.
     */
    static City& GetCity(const string& id);

    /**
     * @brief Checks if a city with the specified ID exists.
     * 
     * @param id The ID of the city.
     * 
     * @pre None.
     * @post True is returned if a city with the specified ID exists, false otherwise.
     * 
     * @return True if a city with the specified ID exists, false otherwise.
     */
    static bool HasCity(const string& id);

    /**
     * @brief Performs trades in the Valley. Trades start recursively from the root node. 
     * The city in the root node trades with its children, which at their time trade with their children, etc.
     * 
     * @pre The Valley is initialized.
     * @post Trades are performed recursively from the root city.
     */
    static void DoTrades();

    /**
     * @brief Gets the best route for the ship.
     * The best route is the shortest route possible where the maximum amount of product is bought and sold.
     * 
     * @pre The Valley is initialized.
     * @post The best route is returned.
     * 
     * @return The best possible route.
     */
    static vector<NavStep> GetBestRoute();

    /**
     * @brief Navigates the specified route, updating the cities of the valley accordingly.
     * 
     * @param route The route to navigate.
     * 
     * @pre The Valley is initialized and the given route is valid.
     * @post The route is navigated and the total number of trades is returned. Cities have been updated with the performed trades, and the 
     * ship has saved the last traded city (if any). The products of the ship, however, have been maintained intact.
     * 
     * @return The total number of trades.
     */
    static int NavigateRoute(const vector<NavStep>& route);
};

#endif
