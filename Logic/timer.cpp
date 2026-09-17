#include "timer.h"


Timer::Timer(QObject *parent): QObject(parent){
    timer = new QTimer(this);
    remainingTime = 0;
    elapsedTime = 0;
    is_running = false;
}

Timer::~Timer(){
    if(deadLine) delete deadLine;
}

void Timer::setMode(TimerMode mode){
    this->mode = mode;
}

void Timer::setDuration(qint64 duration){
    this->duration = duration;
}

void Timer::start(){
    timer->start(1000);
    is_running = true;

    if(mode == TimerMode::countDown){
        deadLine = new QDeadlineTimer(duration);
    }
    else if(mode == TimerMode::countUp){
        elapsedTimer.start();
    }
    connect(timer, &QTimer::timeout, this, &Timer::onTimeout);

}

void Timer::stop(){
    timer->stop();
    is_running = false;

    if(mode == TimerMode::countDown){
        remainingTime = deadLine->remainingTime();
        delete deadLine;
    }
    else{
        elapsedTime = elapsedTimer.elapsed();
    }
}

void Timer::resume(){
    timer->start(1000);
    is_running = true;
    if(mode == TimerMode::countDown){
        deadLine = new QDeadlineTimer(remainingTime);
    }
    else{
        elapsedTimer.restart();
    }
    connect(timer, &QTimer::timeout, this, &Timer::onTimeout);
}

bool Timer::getIsRunning() const{
    return is_running;
}

void Timer::onTimeout(){
    if(mode == TimerMode::countDown){
        if(deadLine->remainingTime() <= 0){
            emit zeroTimerRequested();
            timer->stop();
            return;
        }
        emit TimeChanged(deadLine->remainingTime());
    }
    else{
        emit TimeChanged(elapsedTimer.elapsed() + elapsedTime);
    }
}

TimerMode Timer::getMode() const{
    return mode;
}


void Timer::extendTime(QTime time){
    stop();

    remainingTime += time.msecsSinceStartOfDay();
    resume();
}


