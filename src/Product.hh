#ifndef PRODUCT_HH
#define PRODUCT_HH

using namespace std;

#include "ProductData.hh"

/**
 * @class Product
 * @brief Represents a product. A product object has an available amount and a wanted amount of units, and can be used for trading.
 * 
 * Each product has a weigth and volume associated to it, stored on the ProductReference class.
 */
class Product
{
    private:
        int id; /**< The ID of the product. */
        int wanted_amount; /**< The desired amount of the product. */
        int current_amount; /**< The current amount of the product. */

    public:
        /**
         * @brief Default constructor for the Product class.
         * 
         * @pre None
         * @post An empty, invalid Product object is created. All the attributes are set to zero
         */
        Product();

        /**
         * @brief Constructor for the Product class.
         * 
         * @param id The ID of the product.
         * @param current The current amount of the product.
         * @param wanted The wanted amount of the product.
         * 
         * @pre The ID of the product must be present on ProductReference
         * @post A Product object is created with the given values for its attributes.
         */
        Product(int id, int current, int wanted);

        /**
         * @brief Get the ID of the product.
         * 
         * @pre None
         * @post The ID of the product is returned.
         * 
         * @return The ID of the product.
         */
        int GetId() const;

        /**
         * @brief Get the available amount of the product.
         * 
         * @pre None
         * @post The available amount of the product is returned.
         * 
         * @return The available amount of the product.
         */
        int GetCurrentAmount() const;

        /**
         * @brief Get the predefined wanted amount of the product. This method returns the
         * initially set wanted amount, and does not reflect if the product has been restocked.
         * For a real indicator of how many product units are required, use **GetMissingAmount()**
         * 
         * @pre None
         * @post The predefined wanted amount of the product is returned.
         * 
         * @return The predefined wanted amount of the product.
         */
        int GetWantedAmount() const;

        /**
         * @brief Get the exceeding amount of the product. This method returns 0 if 
         * the product has a negative balance (GetMissingAmount() > 0).
         * The exceeding product is calculated using the following formula: exceeding = max(0, current_amount - wanted_amount)
         * 
         * @pre None
         * @post The exceeding amount of the product is returned.
         * 
         * @return The exceeding amount of the product.
         */
        int GetExceedingAmount() const;

        /**
         * @brief Get the missing amount of the product. This method returns 0 if 
         * the product has a positive balance (GetExceedingAmount() > 0)
         * The missing product is calculated using the following formula: missing = max(0, wanted_amount - current_amount)
         * 
         * @pre None
         * @post The missing amount of the product is returned.
         * 
         * @return The missing amount of the product.
         */
        int GetMissingAmount() const;

        /**
         * @brief Withdraw a certain amount from the product. This method will **not** update 
         * the weights and volumes on any city instance.
         * @param amount The amount to be withdrawn.
         * 
         * @pre The current amount of the product is greater than or equal to the specified amount.
         * @post The current amount of the product is reduced by the specified amount.
         */
        void WithdrawAmount(int amount);

        /**
         * @brief Restock a certain amount of the product. This method will **not** update 
         * the weights and volumes on any city instance.
         * @param amount The amount to be restocked.
         * 
         * @pre None
         * @post The current amount of the product is increased by the specified amount.
         */
        void RestockAmount(int amount);

        /**
         * @brief Get the data of the product from the ProductRefence Database.
         * 
         * @pre None
         * @post The data of the product is returned.
         * 
         * @return The weight and volume of the product in the form of a constant reference to a ProductData object.
         */
        const ProductData& GetData() const;

        /**
         * @brief Get the weight of the product according to the current available amount of product.
         * 
         * @pre None
         * @post The weight of the product is returned.
         * 
         * @return The weight of the product.
         */
        int GetWeight() const;

        /**
         * @brief Get the volume of the product according to the current available amount of product.
         * 
         * @pre None
         * @post The volume of the product is returned.
         * 
         * @return The volume of the product.
         */
        int GetVolume() const;
};

#endif