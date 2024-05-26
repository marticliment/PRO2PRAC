#ifndef SHIP_HH
#define SHIP_HH

#ifndef NO_DIAGRAM
#include <vector>
#include <iostream>
#endif

#include "Product.hh"

using namespace std;

/**
 * @class Ship
 * @brief Represents a ship that navigates through a Valley buying and selling products. 
 * 
 * The ship buys a certain amount of a Product and sells a different amount of a different Product.
 * The ship also keeps a record of the last city visided on every route.
 * 
 */
class Ship
{
    private:
        Product buying_product; /**< The product that the ship buys. */
        Product selling_product; /**< The product that the ship sells. */
        vector<string> visited_cities; /**< The list of visited cities. */

    public:
        /**
         * @brief Default constructor for the Ship class.
         * 
         * @pre None
         * @post A Ship object is created with two empty products.
         */
        Ship();

        /**
         * @brief Constructor for the Ship class.
         * 
         * @param buying The product that the ship buys.
         * @param selling The product that the ship sells.
         * 
         * @pre None
         * @post A Ship object is created with the specified buying and selling products.
         */
        Ship(Product buying, Product selling);

        /**
         * @brief Getter for the buying product.
         * 
         * @pre None
         * @post A reference to the buying product is returned.
         * 
         * @return A reference to the buying product.
         */
        Product& BuyingProduct();

        /**
         * @brief Getter for the selling product.
         * 
         * @pre None
         * @post A reference to the selling product is returned.
         * 
         * @return A reference to the selling product.
         */
        Product& SellingProduct();

        /**
         * @brief Getter for the visited cities.
         * 
         * @pre None
         * @post The list of visited cities is returned.
         * 
         * @return A constant reference to the list of visited cities.
         */
        const vector<string>& GetVisitedCities() const;

        /**
         * @brief Adds a city to the list of visited cities.
         * 
         * @param city The city to be added.
         * 
         * @pre None
         * @post The specified city is added to the list of visited cities.
         */
        void AddVisitedCity(const string& city);

        /**
         * @brief Resets the list of visited cities.
         * 
         * @pre None
         * @post The list of visited cities is cleared.
         */
        void ResetVisitedCities();

        /**
         * @brief Reads ship data (buy and sell products) from a stream.
         * 
         * @param stream The input stream to read from.
         * 
         * @pre The stream is open and in a valid state.
         * @post The ship data is read from the stream and the object is updated accordingly.
         */
        void ReadFromStream(istream& stream);

        /**
         * @brief Deep-copies the current ship instance and its attributes.
         * 
         * @pre None
         * @post The ship has been deep-copied
         * 
         * @return A deep copy of the ship
         */
        Ship Copy()
        {
            auto buying = Product(buying_product.GetId(), buying_product.GetCurrentAmount(), buying_product.GetWantedAmount());
            auto selling = Product(selling_product.GetId(), selling_product.GetCurrentAmount(), selling_product.GetWantedAmount());
            auto copy = Ship(buying, selling);
            copy.visited_cities = visited_cities;
            return copy;
        }
};

#endif