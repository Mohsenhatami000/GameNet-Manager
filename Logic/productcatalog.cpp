#include "productcatalog.h"

ProductCatalog::ProductCatalog(){}

void ProductCatalog::addProduct(Product product){
    productList[product.getName()] = product;
}

void ProductCatalog::removeProduct(QString name){
    productList.erase(name);
}

Product ProductCatalog::getProduct(QString name) const{
    return productList.at(name);
}