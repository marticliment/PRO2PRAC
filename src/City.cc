#include <vector>
#include "City.hh"
#include "ProductData.hh"

City::City()
{
    City("unknown");
}

City::City(string id)
{
    __id = id;
    __weight = 0;
    __volume = 0;
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
        AddProduct(Product(id, current, required));
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

bool City::HasProduct(int id) const
{
    return __inventory.find(id) != __inventory.end();
}

void City::AddProduct(Product p)
{
    __inventory[p.GetId()] = p;
    const ProductData& data = p.GetData();
    __weight += data.GetWeight(p.GetCurrentAmount());
    __volume += data.GetVolume(p.GetCurrentAmount());
}

void City::RemoveProduct(int id)
{
    Product& old_product = __inventory.at(id);
    __inventory.erase(id);
    const ProductData& data = old_product.GetData();
    __weight -= data.GetWeight(old_product.GetCurrentAmount());
    __volume -= data.GetVolume(old_product.GetCurrentAmount());
}

void City::UpdateProduct(Product p)
{
    RemoveProduct(p.GetId());
    AddProduct(p);
}

int City::GetVolume() const
{
    return __volume;
}

int City::GetWeight() const
{
    return __weight;
}