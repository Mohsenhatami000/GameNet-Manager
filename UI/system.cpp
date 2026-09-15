#include "system.h"
#include "ui_system.h"
#include <QTime>


System::System(Platform platform, std::unordered_map<Platform, QString> &PlatformToQString, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::System)
    , timer(this)
    , platform(platform)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->page);
    counter++;
    id = counter;
    setPlatformToString(PlatformToQString);
    Name = PlatformToQString[platform] + "-" + QString("%1").arg(id, 2, 10, QChar('0'));
    ui->label_name1->setText(Name);
    ui->label_name2->setText(Name);
}

int System::counter = 0;

System::~System()
{
    delete ui;
}

void System::on_pushButton_start_session_clicked()
{
    STsession = new StartSessionDialog(Name, this);
    STsession->setPriceManager(priceManager);
    STsession->setPlatform(platform);
    STsession->show();
    connect(STsession, &StartSessionDialog::startBySetTimeRequested, this, &System::startTimerBySetTime);
    connect(STsession, &StartSessionDialog::cancelRequested, this, &System::cancelDialog);
    connect(STsession, &StartSessionDialog::startFreeTimeRequested, this, &System::startFreeTime);
    playerCount = 1;
}


void System::startTimerBySetTime(){

    STsession->close();
    ui->stackedWidget->setCurrentWidget(ui->page_2);
    playerCount = STsession->getPlayerCount();
    ui->label_player_Count->setText(QString(QString::number(playerCount) + " Player(s)"));
    timer.setMode(TimerMode::countDown);
    timer.setDuration(STsession->getTime().msecsSinceStartOfDay());
    timer.start();
    connect(&timer, &Timer::TimeChanged, this, &System::UpdateTime);

}


void System::UpdateTime(qint64 Miliseconds){

    qint64 TimeInMinute = (Miliseconds / 1000) / 60;
    int Hours = (TimeInMinute / 60);
    int Minutes = TimeInMinute % 60;
    int Seconds = (Miliseconds / 1000) % 60;
    qint32 price;

    price = priceManager->getRule(platform, playerCount).calculateMoneyFromTime(QTime(Hours, Minutes, Seconds));

    if(timer.getMode() == TimerMode::countDown){
        qint32 totalPrice = priceManager->getRule(platform, playerCount).calculateMoneyFromTime(STsession->getTime());
        price = totalPrice - price;
    }

    ui->textBrowser_price->setText("PlayedTime Cost: " + QString::number(price));
    ui->textBrowser_price->setAlignment(Qt::AlignCenter);

    ui->label_Timer->setText(
        QString("%1:%2:%3")
            .arg(Hours, 2, 10, QChar('0'))
            .arg(Minutes, 2, 10, QChar('0'))
            .arg(Seconds, 2, 10, QChar('0'))
        );
}

void System::cancelDialog(){
    STsession->close();
    delete STsession;
}
void System::on_pushButton_stop_resume_clicked()
{
    if(timer.getIsRunning()){
        timer.stop();
        ui->pushButton_stop_resume->setText("Resume");
    }
    else{
        timer.resume();
        ui->pushButton_stop_resume->setText("Stop");
    }
}

void System::startFreeTime(){

    STsession->close();
    ui->stackedWidget->setCurrentWidget(ui->page_2);
    timer.setMode(TimerMode::countUp);
    timer.start();
    playerCount = STsession->getPlayerCount();
    ui->label_player_Count->setText(QString(QString::number(playerCount) + " Player(s)"));
    connect(&timer, &Timer::TimeChanged, this, &System::UpdateTime);
}

void System::zeroTimer(){
    ui->label_Timer->setText("00:00:00");
}


void System::setPriceManager(PricingManager *priceManager){
    this->priceManager = priceManager;
}

void System::setPlatformToString(std::unordered_map<Platform, QString> &PlatformToQString){
    for(auto &i : PlatformToQString){
        this->PlatformToQString[i.first] = i.second;
    }
}
