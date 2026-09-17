#include "descriptiondialog.h"
#include "UI/ui_descriptiondialog.h"

DescriptionDialog::DescriptionDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DescriptionDialog)
{
    ui->setupUi(this);
}

DescriptionDialog::~DescriptionDialog()
{
    delete ui;
}

void DescriptionDialog::on_pushButton_close_clicked()
{
    emit backToMainRequested();
}

