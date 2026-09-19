#include "productsdialog.h"
#include "ui_productsdialog.h"

ProductsDialog::ProductsDialog(ProductCatalog *productCatalog, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ProductsDialog)
{
    this->productCatalog = productCatalog;
    ui->setupUi(this);
    setWindowTitle("افزودن محصول");
    const auto& products = productCatalog->getProductList();
    for(const auto &i : products){
        ui->comboBox_items->addItem(i.first);
    }
}

ProductsDialog::~ProductsDialog()
{
    delete ui;
}

void ProductsDialog::on_pushButton_cancel_clicked()
{
    emit cancelRequested();
}


void ProductsDialog::on_pushButton_add_clicked()
{
    emit addProductRequested(ui->comboBox_items->currentText(), ui->spinBox_quantity->value());
}

