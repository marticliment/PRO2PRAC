/**
 * @file
 * @brief Contains the implementation of the Product class
 */

#ifndef NO_DIAGRAM
#endif

#include "Product.hh"
#include "ProductReference.hh"

Product::Product()
{
    Product(0, 0, 0);
}

Product::Product(int id, int current, int required)
{
    this->id = id;
    current_amount = current;
    wanted_amount = required;
}

int Product::GetId() const
{
    return id;
}

int Product::GetCurrentAmount() const
{
    return current_amount;
}

int Product::GetWantedAmount() const
{
    return wanted_amount;
}

int Product::GetExceedingAmount() const
{
    if(current_amount - wanted_amount < 0)
        return 0;
    
    return current_amount - wanted_amount;
}

int Product::GetMissingAmount() const
{
    if(wanted_amount - current_amount < 0) 
        return 0;
    
    return wanted_amount - current_amount;
}

void Product::WithdrawAmount(int amount)
{
    current_amount -= amount;
}

void Product::RestockAmount(int amount)
{
    current_amount += amount;
}

const ProductData& Product::GetData() const
{
    return ProductReference::Get(id);
}

int Product::GetWeight() const
{
    return ProductReference::Get(id).GetWeight(current_amount);
}

int Product::GetVolume() const
{
    return ProductReference::Get(id).GetVolume(current_amount);
}