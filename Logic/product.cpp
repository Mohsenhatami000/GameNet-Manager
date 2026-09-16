#include "product.h"

Product::Product(QString name, int price){
    this->name = name;
    this->price = price;
}

QString Product::getName() const{
    return name;
}

int Product::getPrice() const{
    return price;
}
