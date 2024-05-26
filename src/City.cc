#ifndef NO_DIAGRAM
#include <vector>
#include <algorithm>
#endif

#include "City.hh"
#include "ProductData.hh"
#include "ProductReference.hh"

City::City()
{
    City("INVALId");
}

City::City(string id)
{
    this->id = id;
}

string City::GetId() const
{
    return id;
}

void City::ReadFromStream(istream& stream)
{
    product_inventory.clear();
    product_list.clear();
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
    auto it = product_list.begin();
    while(it != product_list.end())
        result.push_back(*(it++));
    return result;
}

bool City::HasProduct(int id) const
{
    return product_inventory.find(id) != product_inventory.end();
}

void City::AddProduct(Product new_prod)
{
    product_inventory[new_prod.GetId()] = new_prod;
    product_list.insert(new_prod.GetId());
    weight += new_prod.GetWeight();
    volume += new_prod.GetVolume();
}

void City::RemoveProduct(int id)
{
    auto& product = product_inventory.at(id);
    weight -= product.GetWeight();
    volume -= product.GetVolume();
    product_inventory.erase(id);
    product_list.erase(id);
}

void City::UpdateProduct(Product new_prod)
{
    auto& old_prod = product_inventory.at(new_prod.GetId());
    weight -= old_prod.GetWeight();
    volume -= old_prod.GetVolume();

    weight += new_prod.GetWeight();
    volume += new_prod.GetVolume();
    product_inventory[new_prod.GetId()] = new_prod;
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
    auto& this_product_set = this->GetRawProductIds();
    auto& other_product_set = other.GetRawProductIds();
    
    auto this_product_it = this_product_set.begin();
    auto other_product_it = other_product_set.begin();

    while(this_product_it != this_product_set.end() 
        && other_product_it != other_product_set.end())
    {
        if(*this_product_it > *other_product_it)
            other_product_it++;
        else if(*this_product_it < *other_product_it)
            this_product_it++;

        else //(*this_product_it == *other_product_it)
        {
            int product_id = *this_product_it;

            // this -> SELLER
            // other -> BUYER
            int trade_amount = min(
                this->GetProductExceedingAmount(product_id),
                other.GetProductMissingAmount(product_id)
            );
            if(trade_amount != 0)
            {
                this->WithdrawProductAmount(product_id, trade_amount);
                other.RestockProductAmount(product_id, trade_amount);
            } 
            else
            {
                // other -> SELLER
                // this -> BUYER
                trade_amount = min(
                    other.GetProductExceedingAmount(product_id), 
                    this->GetProductMissingAmount(product_id)
                );
                if(trade_amount != 0)
                {
                    other.WithdrawProductAmount(product_id, trade_amount);
                    this->RestockProductAmount(product_id, trade_amount);
                }
            }
            
            this_product_it++;
            other_product_it++;
        }
    }
}

int City::GetProductCurrentAmount(int product_id) const
{
    return product_inventory.at(product_id).GetCurrentAmount();
}

int City::GetProductWantedAmount(int product_id) const
{
    return product_inventory.at(product_id).GetWantedAmount();
}

int City::GetProductExceedingAmount(int product_id) const
{
    return product_inventory.at(product_id).GetExceedingAmount();
}

int City::GetProductMissingAmount(int product_id) const
{
    return product_inventory.at(product_id).GetMissingAmount();
}

void City::WithdrawProductAmount(int product_id, int amount)
{
    auto& product_data = ProductReference::Get(product_id);
    weight -= product_data.GetWeight(amount);
    volume -= product_data.GetVolume(amount);
    product_inventory.at(product_id).WithdrawAmount(amount);
}

void City::RestockProductAmount(int product_id, int amount)
{
    auto& product_data = ProductReference::Get(product_id);
    weight += product_data.GetWeight(amount);
    volume += product_data.GetVolume(amount);
    product_inventory.at(product_id).RestockAmount(amount);
}

const set<int>& City::GetRawProductIds() const
{
    return product_list;
}