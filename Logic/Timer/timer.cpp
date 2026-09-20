#include "timer.h"


Timer::Timer(QObject *parent): QObject(parent){
    timer = new QTimer(this);
    remainingTime = 0;
    elapsedTime = 0;
    is_running = false;
    connect(timer, &QTimer::timeout, this, &Timer::onTimeout);
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
        delete deadLine;
        deadLine = new QDeadlineTimer(duration);
    }
    else if(mode == TimerMode::countUp){
        elapsedTime = 0;
        elapsedTimer.start();
    }
}

void Timer::stop(){

    if(!is_running){
        return;
    }

    timer->stop();
    is_running = false;

    if(mode == TimerMode::countDown && deadLine){
        remainingTime = deadLine->remainingTime();
        delete deadLine;
        deadLine = nullptr;
    }
    else{
        elapsedTime = elapsedTimer.elapsed();
    }
}

void Timer::resume(){

    if(is_running){
        return;
    }

    timer->start(1000);
    is_running = true;
    if(mode == TimerMode::countDown){
        delete deadLine;
        deadLine = new QDeadlineTimer(remainingTime);
    }
    else{
        elapsedTimer.restart();
    }
}

bool Timer::getIsRunning() const{
    return is_running;
}

void Timer::onTimeout(){
    if(mode == TimerMode::countDown){
        if(!deadLine || deadLine->remainingTime() <= 0){
            emit zeroTimerRequested();
            timer->stop();
            is_running = false;
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


