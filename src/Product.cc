#include "Product.hh"

Product::Product()
{
    Product(0, 0, 0);
}

Product::Product(int id, int current, int required)
{
    __id = id;
    __current_amount = current;
    __wanted_amount = required;
}

int Product::GetId() const
{
    return __id;
}

int Product::GetCurrentAmount() const
{
    return __current_amount;
}

int Product::GetWantedAmount() const
{
    return __wanted_amount;
}

int Product::GetExceedingAmount() const
{
    if(__current_amount - __wanted_amount < 0)
        return 0;
    
    return __current_amount - __wanted_amount;
}

int Product::GetMissingAmount() const
{
    if(__wanted_amount - __current_amount < 0) 
        return 0;
    
    return __wanted_amount - __current_amount;
}

void Product::WithdrawAmount(int amount)
{
    __current_amount -= amount;
}

void Product::RestockAmount(int amount)
{
    __current_amount += amount;
}