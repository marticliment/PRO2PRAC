#ifndef PRODUCT_HH
#define PRODUCT_HH

using namespace std;

#include "ProductData.hh"

class Product
{
    private:
        int __id;
        int __wanted_amount;
        int __current_amount;

    public:
        Product();
        Product(int id, int current, int wanted);
        int GetId() const;

        int GetCurrentAmount() const;
        int GetWantedAmount() const;

        int GetExceedingAmount() const;
        int GetMissingAmount() const;

        void WithdrawAmount(int amount);
        void RestockAmount(int amount);

        const ProductData& GetData() const;

};

#endif