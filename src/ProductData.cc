/**
 * @file
 * @brief Contains the implementation of the ProductData class
 */

#include "ProductData.hh"

ProductData::ProductData()
{
    ProductData(0, 0);
}

ProductData::ProductData(int weight, int volume)
{
    this->weight = weight;
    this->volume = volume;
}

int ProductData::GetWeight() const
{
    return weight;
}

int ProductData::GetWeight(int amount) const
{
    return weight * amount;
}

int ProductData::GetVolume() const
{
    return volume;
}

int ProductData::GetVolume(int amount) const
{
    return volume * amount;
}

