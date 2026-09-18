#include "changeplayercountdialog.h"
#include "UI/ui_changeplayercountdialog.h"
#include <QMessageBox>


ChangePlayerCountDialog::ChangePlayerCountDialog(int playerCount, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChangePlayerCountDialog)
{
    ui->setupUi(this);
    this->playerCount = playerCount;
    ui->spinBox_player_count->setValue(playerCount);
}

ChangePlayerCountDialog::~ChangePlayerCountDialog()
{
    delete ui;
}

void ChangePlayerCountDialog::on_pushButton_cancel_clicked()
{
    emit cancelRequested();
}


void ChangePlayerCountDialog::on_pushButton_change_clicked()
{
    if(ui->spinBox_player_count->value() != playerCount){
        playerCount = ui->spinBox_player_count->value();
        playerCountChanged(playerCount);
    }
    else{
        QMessageBox::warning(this, "Invalid input", "player Count must be different!");
    }
}

