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

void MenuDialog::enableExtendTime(){
    ui->pushButton_extend_time->setEnabled(true);
}

void MenuDialog::disableExtendTime(){
    ui->pushButton_extend_time->setDisabled(true);
}
void MenuDialog::on_pushButton_extend_time_clicked()
{
    extendTimeDialog = new ExtendTimeDialog(this);
    extendTimeDialog->show();
    connect(extendTimeDialog, &ExtendTimeDialog::backRequested, this, &MenuDialog::extendBackToMenu);
    connect(extendTimeDialog, &ExtendTimeDialog::extendTimeRequested, this, &MenuDialog::onExtendTime);
}

void MenuDialog::extendBackToMenu(){
    extendTimeDialog->close();
}

void MenuDialog::onExtendTime(QTime time){
    emit extendTimeRequested(time);
    delete extendTimeDialog;

}