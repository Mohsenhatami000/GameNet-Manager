#ifndef PRODUCTCATALOG_H
#define PRODUCTCATALOG_H

#include "product.h"
#include <map>

class ProductCatalog
{
    std::map<QString, Product> productList;

public:
    ProductCatalog();
    void addProduct(Product product);
    void removeProduct(QString name);
    Product getProduct(QString name) const;

};

#endif // PRODUCTCATALOG_H
