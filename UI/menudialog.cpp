#include "menudialog.h"
#include "UI/ui_menudialog.h"

MenuDialog::MenuDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MenuDialog)
    , extendTimeDialog(nullptr)
    , descriptionDialog(nullptr)
    , playerCountDialog(nullptr)
{
    ui->setupUi(this);
    setWindowTitle("تنظیمات جلسه");
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
void MenuDialog::on_pushButton_description_clicked()
{
    if(!descriptionDialog){
        descriptionDialog = new DescriptionDialog(this);
        connect(descriptionDialog, &DescriptionDialog::backToMainRequested, this, &MenuDialog::descriptionBackToMain);
    }
    descriptionDialog->show();
}

void MenuDialog::descriptionBackToMain(){
    descriptionDialog->close();
}

void MenuDialog::on_pushButton_change_player_count_clicked()
{
    if(!playerCountDialog){
        playerCountDialog = new ChangePlayerCountDialog(playerCount, this);
        connect(playerCountDialog, &ChangePlayerCountDialog::cancelRequested, this, &MenuDialog::changePlayerBackToMain);
        connect(playerCountDialog, &ChangePlayerCountDialog::playerCountChanged, this, &MenuDialog::onPlayerCount);
    }
    playerCountDialog->show();
}

void MenuDialog::changePlayerBackToMain(){
    playerCountDialog->close();
    delete playerCountDialog;
    playerCountDialog = nullptr;
}

void MenuDialog::setPlayerCount(int playerCount){
    this->playerCount = playerCount;
}

void MenuDialog::onPlayerCount(int pCount){
    changePlayerBackToMain();
    emit playerCountChanged(pCount);
}
