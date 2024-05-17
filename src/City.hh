#ifndef CITY_HH
#define CITY_HH

#include <map>
#include <iostream>
#include "Product.hh"

using namespace std;

class City
{
    private:
        string __id;
        map<int, Product> inventory;
        int weight = 0;
        int volume = 0;

    public:
        City();
        City(string id);
        string GetId() const;
        void ReadFromStream(istream& stream);
        vector<int> GetProductIds() const;
        
        int GetProductCurrentAmount(int product_id) const;
        int GetProductWantedAmount(int product_id) const;
        int GetProductExceedingAmount(int product_id) const;
        int GetProductMissingAmount(int product_id) const;
        void WithdrawProductAmount(int product_id, int amount);
        void RestockProductAmount(int product_id, int amount);
                
        bool HasProduct(int id) const;
        void AddProduct(Product p);
        void UpdateProduct(Product p);
        void RemoveProduct(int product_id);
        int GetWeight() const;
        int GetVolume() const;
        void TradeWith(City& other);
        const map<int, Product>& GetRawInventory() const;
};

#endif