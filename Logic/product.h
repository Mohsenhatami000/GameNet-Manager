#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>

class Product
{
    QString name;
    int price;

public:
    Product(QString name, int price);
    Product() = default;
    QString getName() const;
    int getPrice() const;
};

#endif // PRODUCT_H
