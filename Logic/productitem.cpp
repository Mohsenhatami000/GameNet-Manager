#include "productitem.h"

ProductItem::ProductItem(Product &product, int quantity): product(product), quantity(quantity){}

Product ProductItem::getProduct() const{
    return product;
}

int ProductItem::getQuantity() const{
    return quantity;
}