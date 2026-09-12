#include "startsessiondialog.h"
#include "ui_startsessiondialog.h"

StartSessionDialog::StartSessionDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StartSessionDialog)
{
    ui->setupUi(this);
}

StartSessionDialog::~StartSessionDialog()
{
    delete ui;
}
