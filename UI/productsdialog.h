#ifndef PRODUCTSDIALOG_H
#define PRODUCTSDIALOG_H

#include <QDialog>
#include "../Logic/productcatalog.h"

namespace Ui {
class ProductsDialog;
}

class ProductsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProductsDialog(ProductCatalog *productCatalog = nullptr, QWidget *parent = nullptr);
    ~ProductsDialog();

private slots:
    void on_pushButton_cancel_clicked();

    void on_pushButton_add_clicked();

signals:
    void cancelRequested();
    void addProductRequested(QString productName, int quantity);

private:
    Ui::ProductsDialog *ui;
    ProductCatalog *productCatalog;
};

#endif // PRODUCTSDIALOG_H
