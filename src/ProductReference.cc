#include "ProductReference.hh"

vector<ProductData> ProductReference::data = vector<ProductData>(0);

void ProductReference::Add(ProductData new_data)
{
    data.push_back(new_data);
}

const ProductData& ProductReference::Get(int id)
{
    if(Contains(id))
        return data[id-1];
    else
        throw exception();
}

bool ProductReference::Contains(int id)
{
    if(id <= 0)
        return false;

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