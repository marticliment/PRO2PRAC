#include <vector>
#include "City.hh"

City::City()
{
    City("unknown");
}

City::City(string id)
{
    __id = id;
}

string City::GetId() const
{
    return __id;
}

void City::ReadFromStream(istream& stream)
{
    int count;
    stream >> count;
    for(int i = 0; i < count; i++)
    {
        int id, current, required;
        stream >> id >> current >> required;
        __inventory[id] = Product(id, current, required);
    }
}

vector<int> City::GetProductIds() const
{
    vector<int> result;
    auto it = __inventory.begin();
    while(it != __inventory.end())
    {
        result.push_back(it->first);
        it++;
    }
    return result;
}

const Product& City::GetProduct(int id) const
{
    return __inventory.at(id);
}