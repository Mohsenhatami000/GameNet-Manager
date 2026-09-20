#include "timeexpireddialog.h"
#include "UI/TimeExpired/ui_timeexpireddialog.h"

TimeExpiredDialog::TimeExpiredDialog(QString msg, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TimeExpiredDialog)
{
    ui->setupUi(this);
    ui->label->setText(msg);
}

TimeExpiredDialog::~TimeExpiredDialog()
{
    delete ui;
}

void TimeExpiredDialog::on_pushButton_end_session_clicked()
{
    endSessionRequested();
}


void TimeExpiredDialog::on_pushButton_extend_time_clicked()
{
    extendTimeRequested();
}

