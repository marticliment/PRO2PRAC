#ifndef PRODUCT_DATA_HH
#define PRODUCT_DATA_HH

class ProductData
{
    private:
        int weight;
        int volume;


    public:
        ProductData();
        ProductData(int weight, int volume);

        int GetWeight() const;
        int GetWeight(int amount) const;
        
        int GetVolume() const;
        int GetVolume(int amount) const;

};

#endif