/**
 * @file
 * @brief Contains the specification of the City class
 */

#ifndef CITY_HH
#define CITY_HH

#ifndef NO_DIAGRAM
#include <unordered_map>
#include <map>
#include <set>
#include <iostream>
#endif

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
        string id; /**< The unique identifier of the city */
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
         * @pre the id string is not empty
         * @post A valid City instance is created with the given identifier. The product inventory is empty by default
         */
        City(string id);

        /**
         * @brief Get the unique identifier of the city.
         * 
         * @return The unique identifier of the city.
         * 
         * @pre The current city instance is valid
         * @post Returns the identifier of the city
         */
        const string& GetId() const;

        /**
         * @brief Read the city product inventory from a stream. The old product inventory will be erased
         * 
         * @param stream The input stream to read from.
         * 
         * @pre The stream is open and valid.
         * @post The city products are read from the stream and saved to the inventory of this instance. Any previous inventory gets lost.
         */
        void ReadFromStream(istream& stream);

        /**
         * @brief Get the Ids of all the products in the city.
         * 
         * @pre None
         * @post None
         * 
         * @return A vector containing the Ids of all the products in the city.
         */
        vector<int> GetProductIds() const;
        
        /**
         * @brief Get the current amount of a product in the city.
         * 
         * @param product_id The Id of the product.
         * 
         * @pre A product with the given Id exists in the city.
         * @post The current amount of the product in the city is returned.
         * 
         * @return The current amount of the product in the city.
         */
        int GetProductCurrentAmount(int product_id) const;

        /**
         * @brief Get the wanted amount of a product in the city. This method returns the
         * initially set wanted amount, and does not reflect if the product has been restocked.
         * For a real indicator of how many product units are required, use **GetProductMissingAmount()**
         * 
         * @param product_id The Id of the product.
         * 
         * @pre A product with the given Id exists in the city.
         * @post The wanted amount of the product in the city is returned.
         * 
         * @return The amount of this product the city wants.
         */
        int GetProductWantedAmount(int product_id) const;

        /**
         * @brief Get the exceeding amount of a product in the city. This method returns 0 if 
         * the product has a negative balance (GetProductMissingAmount() > 0).
         * The exceeding product is calculated using the following formula: exceeding = max(0, current_amount - wanted_amount)
         * 
         * @param product_id The Id of the product.
         * 
         * @pre A product with the given Id exists in the city.
         * @post The exceeding amount of the product in the city is returned.
         * 
         * @return The exceeding amount of the product in the city.
         */
        int GetProductExceedingAmount(int product_id) const;

        /**
         * @brief Get the missing amount of a product in the city. This method returns 0 if 
         * the product has a positive balance (GetProductExceedingAmount() > 0)
         * The missing product is calculated using the following formula: missing = max(0, wanted_amount - current_amount)
         * 
         * @param product_id The Id of the product.
         * 

         * @pre A product with the given Id exists in the city.
         * @post The missing amount of the product in the city is returned.
         * 
         * @return The missing amount of the product in the city.
         */
        int GetProductMissingAmount(int product_id) const;

        /**
         * @brief Withdraw a certain amount of a product from the city.
         * 
         * @param product_id The Id of the product.
         * @param amount The amount to withdraw.
         * 
         * @pre A product with the given Id exists in the city, and the amount to withdraw meets **0 <= withdraw_amount <= current_amount**
         * @post The amount of the product in the city is reduced by the specified amount. 
         * The total weight and volume of the city are updated accordingly
         */
        void WithdrawProductAmount(int product_id, int amount);

        /**
         * @brief Restock a certain amount of a product in the city.
         * 
         * @param product_id The Id of the product.
         * @param amount The amount to restock.
         * 
         * @pre The product with the given Id exists in the city, and the amount to restock meets **0 <= restock_amount**
         * @post The amount of the product in the city is increased by the specified amount.
         * The total weight and volume of the city are updated accordingly
         */
        void RestockProductAmount(int product_id, int amount);
                
        /**
         * @brief Check if the city has a product with the given Id.
         * 
         * @param id The Id of the product.
         * 
         * @pre The id fulfills **0 < Id <= product_count**
         * @post None
         * 
         * @return True if the city has the product, false otherwise.
         */
        bool HasProduct(int id) const;

        /**
         * @brief Add a product to the city's inventory.
         * 
         * @param new_prod The product to add.
         * 
         * @pre There is not any product in the city that has the same Id
         * as the product that is going to be added.
         * @post The product is added to the city's inventory.
         * The total weight and volume of the city are updated accordingly
         */
        void AddProduct(const Product& new_prod);

        /**
         * @brief Update a product in the city's inventory.
         * 
         * @param new_prod The product to update.
         * 
         * @pre A product with the same Id already exists in the city.
         * @post The product in the city's inventory is replaced with the given product.
         * The total weight and volume of the city are updated accordingly
         */
        void UpdateProduct(const Product& new_prod);

        /**
         * @brief Remove a product from the city's inventory.
         * 
         * @param product_id The Id of the product to remove.
         * 
         * @pre A product with the given Id exists in the city.
         * @post The product is removed from the city's inventory.
         * The total weight and volume of the city are updated accordingly
         */
        void RemoveProduct(int product_id);

        /**
         * @brief Get the total weight of the products in the city.
         * 
         * @pre The Id fulfills **0 < Id <= product_count**
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
         * @pre Both cities are valid.
         * @post All the possible trades between the two cities are performed. 
         */
        void TradeWith(City& other);

        /**
         * @brief Get the set of raw product Ids in the city. This method 
         * is designed to be able to access the iterators on the set<int> containing
         * the products. Under normal circumstances **GetProductIds()** should be used instead
         * 
         * @pre None
         * @post None
         * 
         * @return The raw set of product Ids in the city.
         */
        const set<int>& GetRawProductIds() const;
};

#endif