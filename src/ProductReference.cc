/**
 * @file
 * @brief Contains the implementation of the ProductReference <i>static</i> class
 */

#ifndef NO_DIAGRAM
#include <vector>
#include <iostream>
#endif

#include "ProductReference.hh"

vector<ProductData> ProductReference::data;

void ProductReference::Add(ProductData new_data)
{
    data.push_back(new_data);
}

const ProductData& ProductReference::Get(int id)
{
    return data[id-1];
}

bool ProductReference::Contains(int id)
{
    return id <= data.size();
}

void ProductReference::AddFromStream(istream& stream, int count)
{
    for(int i = 0; i < count; i++)
    {
        int weight, volume;
        stream >> weight >> volume;
        ProductReference::Add(ProductData(weight, volume));
    }
}

int ProductReference::Count()
{
    return data.size();
}