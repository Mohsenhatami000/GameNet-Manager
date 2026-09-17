#include "extendtimedialog.h"
#include "UI/ui_extendtimedialog.h"

ExtendTimeDialog::ExtendTimeDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ExtendTimeDialog)
{
    ui->setupUi(this);
    time.setHMS(1, 0, 0);
}

ExtendTimeDialog::~ExtendTimeDialog()
{
    delete ui;
}

void ExtendTimeDialog::on_pushButton_back_clicked()
{
    emit backRequested();
}


void ExtendTimeDialog::on_pushButton_15Min_clicked()
{
    time.setHMS(0, 15, 0);
    ui->timeEdit_time->setTime(time);
}


void ExtendTimeDialog::on_pushButton_30Min_clicked()
{
    time.setHMS(0, 30, 0);
    ui->timeEdit_time->setTime(time);
}


void ExtendTimeDialog::on_pushButton_1Hour_clicked()
{
    time.setHMS(1, 0, 0);
    ui->timeEdit_time->setTime(time);
}


void ExtendTimeDialog::on_pushButton_2Hour_clicked()
{
    time.setHMS(2, 0, 0);
    ui->timeEdit_time->setTime(time);
}


void ExtendTimeDialog::on_pushButton_extend_clicked()
{
    emit extendTimeRequested(time);
}

