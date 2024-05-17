#ifndef CITY_HH
#define CITY_HH

#include <unordered_map>
#include <map>
#include <set>
#include <iostream>
#include "Product.hh"

using namespace std;

/**
 * @class City
 * @brief Represents a city with an inventory of Product items.
 * 
 * The City class stores information about a city, including its unique identifier,
 * inventory of products, weight, and volume. It provides methods to manage the inventory,
 * such as adding, updating, and removing products, as well as retrieving information about
 * the products and trading with other cities.
 */
class City
{
    private:
        string __id; /**< The unique identifier of the city */
        unordered_map<int, Product> product_inventory; /**< The inventory of products in the city */
        set<int> product_list; /**< The "list" products the city has */
        int weight = 0; /**< The total weight of the products in the city */
        int volume = 0; /**< The total volume of the products in the city */

    public:
        /**
         * @brief Default constructor for the City class.
         * 
         * @pre None
         * @post An invalid, empty City object is created.
         */
        City();

        /**
         * @brief Constructor for the City class.
         * 
         * @param id The unique, non-empty identifier of the city.
         * 
         * @pre None
         * @post A City object is created with the given identifier. The product inventory is empty by default
         */
        City(string id);

        /**
         * @brief Get the unique identifier of the city.
         * 
         * @return The unique identifier of the city.
         * 
         * @pre None
         * @post None
         */
        string GetId() const;

        /**
         * @brief Read the city product inventory from a stream. The old product inventory will be erased
         * 
         * @param stream The input stream to read from.
         * 
         * @pre The stream is open and valid.
         * @post The city products are read from the stream and saved to the inventory.
         */
        void ReadFromStream(istream& stream);

        /**
         * @brief Get the IDs of all the products in the city.
         * 
         * @pre None
         * @post None
         * 
         * @return A vector containing the IDs of all the products in the city.
         */
        vector<int> GetProductIds() const;
        
        /**
         * @brief Get the current amount of a product in the city.
         * 
         * @param product_id The ID of the product.
         * 
         * @pre The product with the given ID exists in the city.
         * @post None
         * 
         * @return The current amount of the product in the city.
         */
        int GetProductCurrentAmount(int product_id) const;

        /**
         * @brief Get the wanted amount of a product in the city. The *wanted amount 
         * does **not** reflect wether the city has fullfilled its needs. To get a real "missing"
         * product counter, `GetProductMissingAmount()` should be used instead
         * 
         * @param product_id The ID of the product.
         * 
         * @pre The product with the given ID exists in the city.
         * @post None
         * 
         * @return The wanted amount of the product in the city.
         */
        int GetProductWantedAmount(int product_id) const;

        /**
         * @brief Get the exceeding amount of a product in the city.
         * 
         * @param product_id The ID of the product.
         * 
         * @pre The product with the given ID exists in the city.
         * @post None
         * 
         * @return The exceeding amount of the product in the city.
         */
        int GetProductExceedingAmount(int product_id) const;

        /**
         * @brief Get the missing amount of a product in the city.
         * 
         * @param product_id The ID of the product.
         * 
         * @pre The product with the given ID exists in the city.
         * @post None
         * 
         * @return The missing amount of the product in the city.
         */
        int GetProductMissingAmount(int product_id) const;

        /**
         * @brief Withdraw a certain amount of a product from the city.
         * 
         * @param product_id The ID of the product.
         * @param amount The amount to withdraw.
         * 
         * @pre The product with the given ID exists in the city.
         * @post The amount of the product in the city is reduced by the specified amount. 
         * The total weight and volume of the city are updated accordingly
         */
        void WithdrawProductAmount(int product_id, int amount);

        /**
         * @brief Restock a certain amount of a product in the city.
         * 
         * @param product_id The ID of the product.
         * @param amount The amount to restock.
         * 
         * @pre The product with the given ID exists in the city.
         * @post The amount of the product in the city is increased by the specified amount.
         * The total weight and volume of the city are updated accordingly
         */
        void RestockProductAmount(int product_id, int amount);
                
        /**
         * @brief Check if the city has a product with the given ID.
         * 
         * @param id The ID of the product.
         * @return True if the city has the product, false otherwise.
         * 
         * @pre None
         * @post None
         */
        bool HasProduct(int id) const;

        /**
         * @brief Add a product to the city's inventory.
         * 
         * @param p The product to add.
         * 
         * @pre None
         * @post The product is added to the city's inventory.
         * The total weight and volume of the city are updated accordingly
         */
        void AddProduct(Product p);

        /**
         * @brief Update a product in the city's inventory.
         * 
         * @param p The product to update.
         * 
         * @pre The product with the same ID as the given product exists in the city.
         * @post The product in the city's inventory is replaced with the given product.
         * The total weight and volume of the city are updated accordingly
         */
        void UpdateProduct(Product p);

        /**
         * @brief Remove a product from the city's inventory.
         * 
         * @param product_id The ID of the product to remove.
         * 
         * @pre The product with the given ID exists in the city.
         * @post The product is removed from the city's inventory.
         * The total weight and volume of the city are updated accordingly
         */
        void RemoveProduct(int product_id);

        /**
         * @brief Get the total weight of the products in the city.
         * 
         * @pre None
         * @post None
         * 
         * @return The total weight of the products in the city.
         */
        int GetWeight() const;

        /**
         * @brief Get the total volume of the products in the city.
         * 
         * @pre None
         * @post None
         * 
         * @return The total volume of the products in the city.
         */
        int GetVolume() const;

        /**
         * @brief Trade products with another city. The two cities may or may not have products in common.
         * 
         * @param other The other city to trade with.
         * 
         * @pre The other city is valid.
         * @post The products are traded between the two cities.
         */
        void TradeWith(City& other);

        /**
         * @brief Get the set of raw product IDs in the city. This method 
         * is designed to be able to access the iterators on the set<int> containing
         * the products. Under normal circumstances **GetProductIds()** should be used instead
         * 
         * @pre None
         * @post None
         * 
         * @return The set of raw product IDs in the city.
         */
        const set<int>& GetRawProductIds() const;
};

#endif