#include "productitem.h"

ProductItem::ProductItem(Product product, int quantity): product(product), quantity(quantity){}

Product ProductItem::getProduct() const{
    return product;
}

int ProductItem::getQuantity() const{
    return quantity;
}


void ProductItem::operator+=(const ProductItem& item){
    if(product.getName() == item.product.getName()){
        quantity += item.quantity;
    }
}