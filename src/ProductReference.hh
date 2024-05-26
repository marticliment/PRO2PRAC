#ifndef PRODUCTREFERENCE_HH
#define PRODUCTREFERENCE_HH

#ifndef NO_DIAGRAM
#include <vector>
#include <iostream>
#endif

#include "Product.hh"
#include "ProductData.hh"

using namespace std;

/**
 * @class ProductReference
 * @brief Stores the data (in ProductData objects) and keeps track of all the existing products.
 * 
 */
class ProductReference
{
private:
    static vector<ProductData> data; /**< The product database. ProductData instances are stored here, where the index is the product Id */

public:
    /**
     * @brief Adds a new product data to the reference
     * 
     * @param new_data The product data to be added.
     * 
     * @pre The new_data must be a valid ProductData object.
     * @post The new_data is added to the reference.
     */
    static void Add(ProductData new_data);

    /**
     * @brief Adds multiple product data from an input stream to the reference.
     * 
     * @param reader The input stream to read the product data from.
     * @param count The number of product data to be read and added.
     * 
     * @pre The reader must be a valid input stream, and the count must be a positive integer.
     * @post The product data read from the stream is added to the reference.
     */
    static void AddFromStream(istream& reader, int count);

    /**
     * @brief Retrieves the product data with the specified Id from the reference.
     * 
     * @param id The Id of the product data to retrieve.
     * 
     * @pre The Id must be a valid Id of an existing product data in the reference.
     * @post The product data with the specified Id is returned.
     * 
     * @return The product data with the specified Id.
     */
    static const ProductData& Get(int id);

    /**
     * @brief Checks if the reference contains product data with the specified Id.
     * 
     * @param id The Id to check.
     * 
     * @pre The Id must be a valid Id.
     * @post Returns true if the reference contains product data with the specified Id, false otherwise.
     * 
     * @return True if the reference contains product data with the specified Id, false otherwise.
     */
    static bool Contains(int id);

    /**
     * @brief Retrieves the number of product data in the reference.
     * 
     * @post Returns the number of product data in the reference.
     * 
     * @return The number of product data in the reference.
     */
    static int Count();
};

#endif