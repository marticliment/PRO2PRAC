#ifndef PRODUCT_HH
#define PRODUCT_HH

using namespace std;

#include "ProductData.hh"

class Product
{
    private:
        int id;
        int wanted_amount;
        int current_amount;

    public:
        Product();
        Product(int id, int current, int wanted);
        int GetId() const;

        int GetCurrentAmount() const;
        int GetWantedAmount() const;

        int ExceedingAmount() const;
        int MissingAmount() const;

        void WithdrawAmount(int amount);
        void RestockAmount(int amount);

        const ProductData& GetData() const;
        int GetWeight() const;
        int GetVolume() const;

};

#endif