#include "ProductReference.hh"

vector<ProductData> ProductReference::__data = vector<ProductData>(0);

void ProductReference::Add(ProductData data)
{
    __data.push_back(data);
}

ProductData& ProductReference::Get(int id)
{
    if(Contains(id))
        return __data[id-1];
    else
        throw exception();
}

bool ProductReference::Contains(int id)
{
    return id <= __data.size();
}