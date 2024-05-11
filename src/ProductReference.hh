#ifndef PRODUCTREFERENCE_HH
#define PRODUCTREFERENCE_HH

#include <vector>
#include "Product.hh"
#include "ProductData.hh"

using namespace std;

class ProductReference
{
    private:
        static vector<ProductData> __data;


    public:
        static void Add(ProductData data);
        static ProductData& Get(int id);
        static bool Contains(int id);
};

#endif