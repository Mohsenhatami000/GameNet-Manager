#include "startsessiondialog.h"
#include "ui_startsessiondialog.h"


StartSessionDialog::StartSessionDialog(QString Name, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StartSessionDialog)
{
    this->Name = Name;
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->page_4);
    ui->label_titr->setText(QString("Start Session - ") + Name);
    time.setHMS(1, 0, 0);
    playerCount = 1;
}

StartSessionDialog::~StartSessionDialog()
{
    delete ui;
}

void StartSessionDialog::on_pushButton_set_time_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}


void StartSessionDialog::on_pushButton_set_price_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}


void StartSessionDialog::on_pushButton_free_time_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}


void StartSessionDialog::on_pushButton_30Min_clicked()
{
    ui->timeEdit_time->setTime(QTime(0, 30));
    time.setHMS(0, 30, 0);
}


void StartSessionDialog::on_pushButton_1Hour_clicked()
{
    ui->timeEdit_time->setTime(QTime(1, 0));
    time.setHMS(1, 0, 0);
}


void StartSessionDialog::on_pushButton_1_5Hour_clicked()
{
    ui->timeEdit_time->setTime(QTime(1, 30));
    time.setHMS(1, 30, 0);
}


void StartSessionDialog::on_pushButton_2Hour_clicked()
{
    ui->timeEdit_time->setTime(QTime(2, 0));
    time.setHMS(2, 0, 0);
}


void StartSessionDialog::on_pushButton_Start1_clicked()
{
    startBySetTimeRequested();
}


void StartSessionDialog::on_pushButton_cancel1_clicked()
{
    cancelRequested();
}


void StartSessionDialog::on_pushButton_cancel2_clicked()
{
    cancelRequested();
}


void StartSessionDialog::on_pushButton_cancel2_2_clicked()
{
    cancelRequested();
}


void StartSessionDialog::on_pushButton_start2_2_clicked()
{
    startFreeTimeRequested();
}


void StartSessionDialog::on_timeEdit_time_userTimeChanged(const QTime &time)
{
    this->time.setHMS(time.hour(), time.minute(), 0);
}


QTime StartSessionDialog::getTime() const{
    return time;
}

void StartSessionDialog::setPriceManager(PricingManager *priceManager){
    this->priceManager = priceManager;
}

void StartSessionDialog::setPlatform(Platform platform){
    this->platform = platform;
}

void StartSessionDialog::on_pushButton_calculate_clicked()
{
    time = priceManager->getRule(platform, ui->spinBox_player_count2->value()).calculateTimeFromMoney(ui->lineEdit_price->displayText().toInt());
    ui->label_show_time->setText(time.toString("hh:mm:ss"));
}

void StartSessionDialog::on_pushButton_start2_clicked()
{
    startBySetTimeRequested();
}

void StartSessionDialog::on_spinBox_player_count1_valueChanged(int arg1)
{
    playerCount = arg1;
}

int StartSessionDialog::getPlayerCount() const{
    return playerCount;
}
void StartSessionDialog::on_spinBox_player_count2_valueChanged(int arg1)
{
    playerCount = arg1;
}


void StartSessionDialog::on_spinBox_player_count3_valueChanged(int arg1)
{
    playerCount = arg1;
}
