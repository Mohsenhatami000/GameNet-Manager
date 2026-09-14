#ifndef SYSTEM_H
#define SYSTEM_H

#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QDeadlineTimer>
#include <QElapsedTimer>
#include "startsessiondialog.h"

namespace Ui {
class System;
}

class System : public QWidget
{
    Q_OBJECT

public:
    explicit System(QWidget *parent = nullptr);
    ~System();

private slots:
    void on_pushButton_start_session_clicked();
    void startTimerBySetTime();
    void countDownUpdateTime();
    void cancelDialog();
    void startFreeTime();
    void freeTimeUpdateTime();
    void on_pushButton_stop_resume_clicked();

private:
    Ui::System *ui;
    QTimer *timer;
    QElapsedTimer elapsedTimer;
    QDeadlineTimer *deadLine;
    StartSessionDialog *STsession;
    bool is_running;
    bool is_countDown;
    qint64 remainingTime;
    qint64 elapsedTimeBefore;




};

#endif // SYSTEM_H
