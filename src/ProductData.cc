#include "ProductData.hh"

ProductData::ProductData()
{
    ProductData(0, 0);
}

ProductData::ProductData(int weight, int volume)
{
    __weight = weight;
    __volume = volume;
}

int ProductData::GetWeight() const
{
    return __weight;
}

int ProductData::GetWeight(int amount) const
{
    return __weight * amount;
}

int ProductData::GetVolume() const
{
    return __volume;
}

int ProductData::GetVolume(int amount) const
{
    return __volume * amount;
}

