#ifndef PRODUCTITEM_H
#define PRODUCTITEM_H

#include "product.h"

class ProductItem
{
    Product product;
    int quantity;

public:
    ProductItem() = default;
    ProductItem(Product product, int quantity);
    Product getProduct() const;
    int getQuantity() const;
    void operator+=(const ProductItem& item);

};

#endif // PRODUCTITEM_H
