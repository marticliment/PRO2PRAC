#ifndef PRODUCT_HH
#define PRODUCT_HH

using namespace std;

class Product
{
    private:
        int __id;
        int __required_amount;
        int __current_amount;

    public:
        Product();
        Product(int id, int current, int required);
        int GetId() const;

        int GetCurrentAmount() const;
        int GetExceedingAmount() const;
        int GetMissingAmount() const;

        void WithdrawAmount(int amount);
        void RestockAmount(int amount);

};

#endif