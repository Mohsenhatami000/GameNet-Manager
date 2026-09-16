#ifndef PRODUCTITEM_H
#define PRODUCTITEM_H

#include "product.h"

class ProductItem
{
    Product product;
    int quantity;

public:
    ProductItem(Product &product, int quantity);
    Product getProduct() const;
    int getQuantity() const;
};

#endif // PRODUCTITEM_H
