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

Product& City::GetProduct(int id)
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
}

void City::RemoveProduct(int id)
{
    __inventory.erase(id);
}

void City::UpdateProduct(Product p)
{
    RemoveProduct(p.GetId());
    AddProduct(p);
}

int City::GetVolume() const
{
    int volume = 0;
    auto it = __inventory.begin();
    while(it != __inventory.end())
        volume += (it++)->second.GetVolume();
    return volume;
}

int City::GetWeight() const
{
    int weight = 0;
    auto it = __inventory.begin();
    while(it != __inventory.end())
        weight += (it++)->second.GetWeight();
    return weight;
}

void City::Trade(City& other)
{
    for(int product_id: this->GetProductIds())
    {
        // this -> SELLER
        // other -> BUYER
        if(!other.HasProduct(product_id))
            continue;
        else
        {
            auto& seller_product = this->GetProduct(product_id);
            auto& buyer_product = other.GetProduct(product_id);
            if(seller_product.ExceedingAmount() == 0 || buyer_product.MissingAmount() == 0)
                continue;

            int trade_amount = min(seller_product.ExceedingAmount(), buyer_product.MissingAmount());
            seller_product.WithdrawAmount(trade_amount);
            buyer_product.RestockAmount(trade_amount);
        }
    }

    for(int product_id: other.GetProductIds())
    {
        // other -> SELLER
        // this -> BUYER
        if(!this->HasProduct(product_id))
            continue;
        else
        {
            auto& seller_product = other.GetProduct(product_id);
            auto& buyer_product = this->GetProduct(product_id);
            if(seller_product.ExceedingAmount() == 0 || buyer_product.MissingAmount() == 0)
                continue;

            int trade_amount = min(seller_product.ExceedingAmount(), buyer_product.MissingAmount());
            seller_product.WithdrawAmount(trade_amount);
            buyer_product.RestockAmount(trade_amount);
        }
    }
}