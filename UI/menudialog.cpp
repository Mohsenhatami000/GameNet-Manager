#include "menudialog.h"
#include "UI/ui_menudialog.h"

MenuDialog::MenuDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MenuDialog)
{
    ui->setupUi(this);
}

MenuDialog::~MenuDialog()
{
    delete ui;
}

void MenuDialog::on_pushButton_back_clicked()
{
    emit cancelRequested();
}

