#include "system.h"
#include "ui_system.h"
#include <QTime>

System::System(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::System)
    , is_running(true)
{
    ui->setupUi(this);
    elapsedTimeBefore = 0;
    timer = new QTimer(this);
    ui->stackedWidget->setCurrentWidget(ui->page);

}

System::~System()
{
    delete ui;
}

void System::on_pushButton_start_session_clicked()
{
    STsession = new StartSessionDialog(this);
    STsession->show();
    connect(STsession, &StartSessionDialog::startBySetTimeRequested, this, &System::startTimerBySetTime);
    connect(STsession, &StartSessionDialog::cancelRequested, this, &System::cancelDialog);
    connect(STsession, &StartSessionDialog::startFreeTimeRequested, this, &System::startFreeTime);
}


void System::startTimerBySetTime(){

    STsession->close();
    ui->stackedWidget->setCurrentWidget(ui->page_2);
    deadLine = new QDeadlineTimer(STsession->getTime().msecsSinceStartOfDay());
    timer->start(1000);
    is_countDown = true;
    connect(timer, &QTimer::timeout, this, &System::countDownUpdateTime);
}


void System::countDownUpdateTime(){

    qint64 remainingTimeInMS = deadLine->remainingTime();
    if(remainingTimeInMS <= 0){
        timer->stop();
        ui->label_Timer->setText("00:00:00");
        return;
    }

    qint64 remainingTimeInMinute = (remainingTimeInMS / 1000) / 60;
    int Hours = (remainingTimeInMinute / 60);
    int Minutes = remainingTimeInMinute % 60;
    int Seconds = (remainingTimeInMS / 1000) % 60;

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
    if(is_running){
        if(is_countDown){
            timer->stop();
            remainingTime = deadLine->remainingTime();
            delete deadLine;
            ui->pushButton_stop_resume->setText("Resume");
            is_running = false;
        }
        else{
            elapsedTimeBefore += elapsedTimer.elapsed();
            timer->stop();
            ui->pushButton_stop_resume->setText("Resume");
            is_running = false;
        }
    }
    else{
        if(is_countDown){
            deadLine = new QDeadlineTimer(remainingTime);
            timer->start(1000);
            connect(timer, &QTimer::timeout, this, &System::countDownUpdateTime);
            ui->pushButton_stop_resume->setText("Stop");
            is_running = true;
        }
        else{
            elapsedTimer.restart();
            timer->start(1000);
            ui->pushButton_stop_resume->setText("Stop");
            is_running = true;
        }
    }

}

void System::startFreeTime(){

    STsession->close();
    ui->stackedWidget->setCurrentWidget(ui->page_2);
    elapsedTimer.start();
    timer->start(1000);
    is_countDown = false;
    connect(timer, &QTimer::timeout, this, &System::freeTimeUpdateTime);
}

void System::freeTimeUpdateTime(){
    qint64 elapsedTimeInMS = elapsedTimer.elapsed() + elapsedTimeBefore;
    qint64 elapsedTimeInMinute = (elapsedTimeInMS / 1000) / 60;
    int Hours = (elapsedTimeInMinute / 60);
    int Minutes = elapsedTimeInMinute % 60;
    int Seconds = (elapsedTimeInMS / 1000) % 60;

    ui->label_Timer->setText(
        QString("%1:%2:%3")
            .arg(Hours, 2, 10, QChar('0'))
            .arg(Minutes, 2, 10, QChar('0'))
            .arg(Seconds, 2, 10, QChar('0'))
        );
}

