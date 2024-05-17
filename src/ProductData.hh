#ifndef PRODUCT_DATA_HH
#define PRODUCT_DATA_HH

/**
 * @class ProductData
 * @brief Class representing the data (weight and volume) for a specific product.
 *
 * This class stores information about the weight and volume of a product.
 */
class ProductData
{
    private:
        int weight; /**< The weight of the product. */
        int volume; /**< The volume of the product. */

    public:
        /**
         * @brief Default constructor.
         *
         * Initializes the weight and volume to 0.
         *
         * @pre None
         * @post The weight and volume are set to 0.
         */
        ProductData();

        /**
         * @brief Constructor with parameters.
         *
         * Initializes the weight and volume with the given values.
         *
         * @param weight The weight of the product per unit of product.
         * @param volume The volume of the product per unit of product.
         * @pre None
         * @post The weight and volume are set to the given values.
         */
        ProductData(int weight, int volume);

        /**
         * @brief Get the weight of one unit the product.
         *
         * @return The weight of one unit of the product.
         * @pre None
         * @post None
         */
        int GetWeight() const;

        /**
         * @brief Get the total weight of the product.
         *
         * Calculates the total weight of the product based on the given amount.
         *
         * @param amount The amount of the product.
         * @return The total weight of the product.
         * @pre None
         * @post None
         */
        int GetWeight(int amount) const;
        
        /**
         * @brief Get the volume of one unit of the product.
         *
         * @return The volume of one unit of the product.
         * @pre None
         * @post None
         */
        int GetVolume() const;

        /**
         * @brief Get the total volume of the product.
         *
         * Calculates the total volume of the product based on the given amount.
         *
         * @param amount The amount of the product.
         * @return The total volume of the product.
         * @pre None
         * @post None
         */
        int GetVolume(int amount) const;

};

#endif