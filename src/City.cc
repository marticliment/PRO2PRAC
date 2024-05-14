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
    inventory.clear();
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
    auto it = inventory.begin();
    while(it != inventory.end())
    {
        result.push_back(it->first);
        it++;
    }
    return result;
}

/*Product& City::GetProduct(int id)
{
    return inventory.at(id);
}*/

bool City::HasProduct(int id) const
{
    return inventory.find(id) != inventory.end();
}

void City::AddProduct(Product p)
{
    inventory[p.GetId()] = p;
}

void City::RemoveProduct(int id)
{
    inventory.erase(id);
}

void City::UpdateProduct(Product p)
{
    RemoveProduct(p.GetId());
    AddProduct(p);
}

int City::GetVolume() const
{
    int volume = 0;
    auto it = inventory.begin();
    while(it != inventory.end())
        volume += (it++)->second.GetVolume();
    return volume;
}

int City::GetWeight() const
{
    int weight = 0;
    auto it = inventory.begin();
    while(it != inventory.end())
        weight += (it++)->second.GetWeight();
    return weight;
}

void City::TradeWith(City& other)
{
    for(int product_id: this->GetProductIds())
    {
        // this -> SELLER
        // other -> BUYER
        if(!other.HasProduct(product_id))
            continue;
        else
        {
            if(this->GetProductExceedingAmount(product_id) == 0 || other.GetProductMissingAmount(product_id) == 0)
                continue;

            int trade_amount = min(this->GetProductExceedingAmount(product_id), other.GetProductMissingAmount(product_id));
            this->WithdrawProductAmount(product_id, trade_amount);
            other.RestockProductAmount(product_id, trade_amount);
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
            if(other.GetProductExceedingAmount(product_id) == 0 || this->GetProductMissingAmount(product_id) == 0)
                continue;

            int trade_amount = min(other.GetProductExceedingAmount(product_id), this->GetProductMissingAmount(product_id));
            other.WithdrawProductAmount(product_id, trade_amount);
            this->RestockProductAmount(product_id, trade_amount);
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
    inventory.at(product_id).WithdrawAmount(amount);
}

void City::RestockProductAmount(int product_id, int amount)
{
    inventory.at(product_id).RestockAmount(amount);
}