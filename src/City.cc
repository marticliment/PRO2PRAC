#include <vector>
#include <algorithm>
#include "City.hh"
#include "ProductData.hh"
#include "ProductReference.hh"

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
    inventory.clear();
    products.clear();
    weight = 0;
    volume = 0;
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
    auto it = products.begin();
    while(it != products.end())
        result.push_back(*(it++));
    return result;
}

bool City::HasProduct(int id) const
{
    return inventory.find(id) != inventory.end();
}

void City::AddProduct(Product p)
{
    inventory[p.GetId()] = p;
    products.insert(p.GetId());
    weight += p.GetWeight();
    volume += p.GetVolume();
}

void City::RemoveProduct(int id)
{
    auto& product = inventory.at(id);
    weight -= product.GetWeight();
    volume -= product.GetVolume();
    inventory.erase(id);
    products.erase(id);
}

void City::UpdateProduct(Product p)
{
    RemoveProduct(p.GetId());
    AddProduct(p);
}

int City::GetVolume() const
{
    return volume;
}

int City::GetWeight() const
{
    return weight;
}

void City::TradeWith(City& other)
{
    auto& this_inventory = this->GetRawProductIds();
    auto& other_inventory = other.GetRawProductIds();
    
    auto this_product = this_inventory.begin();
    auto other_product = other_inventory.begin();
    while(this_product != this_inventory.end() && other_product != other_inventory.end())
    {
        if(*this_product > *other_product)
        {
            other_product++;
        }
        else if(*this_product < *other_product)
        {
            this_product++;
        }
        else // The product is present on both cities
        {
            int product_id = *this_product;

            if(this->GetProductExceedingAmount(product_id) != 0 && other.GetProductMissingAmount(product_id) != 0)
            {
                // this -> SELLER
                // other -> BUYER
                int trade_amount = min(this->GetProductExceedingAmount(product_id), other.GetProductMissingAmount(product_id));
                this->WithdrawProductAmount(product_id, trade_amount);
                other.RestockProductAmount(product_id, trade_amount);
            } 
            else if(other.GetProductExceedingAmount(product_id) != 0 && this->GetProductMissingAmount(product_id) != 0)
            {
                // other -> SELLER
                // this -> BUYER
                int trade_amount = min(other.GetProductExceedingAmount(product_id), this->GetProductMissingAmount(product_id));
                other.WithdrawProductAmount(product_id, trade_amount);
                this->RestockProductAmount(product_id, trade_amount);
            }
            
            this_product++;
            other_product++;
        }
    }
}

int City::GetProductCurrentAmount(int product_id) const
{
    return inventory.at(product_id).GetCurrentAmount();
}

int City::GetProductWantedAmount(int product_id) const
{
    return inventory.at(product_id).GetWantedAmount();
}

int City::GetProductExceedingAmount(int product_id) const
{
    return inventory.at(product_id).GetExceedingAmount();
}

int City::GetProductMissingAmount(int product_id) const
{
    return inventory.at(product_id).GetMissingAmount();
}

void City::WithdrawProductAmount(int product_id, int amount)
{
    auto& product_data = ProductReference::Get(product_id);
    weight -= product_data.GetWeight(amount);
    volume -= product_data.GetVolume(amount);
    inventory.at(product_id).WithdrawAmount(amount);
}

void City::RestockProductAmount(int product_id, int amount)
{
    auto& product_data = ProductReference::Get(product_id);
    weight += product_data.GetWeight(amount);
    volume += product_data.GetVolume(amount);
    inventory.at(product_id).RestockAmount(amount);
}

const set<int>& City::GetRawProductIds() const
{
    return products;
}