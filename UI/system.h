#ifndef SYSTEM_H
#define SYSTEM_H

#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QDeadlineTimer>
#include <QElapsedTimer>
#include "startsessiondialog.h"
#include "../Logic/timer.h"
#include "../Logic/pricingmanager.h"

namespace Ui {
class System;
}

class System : public QWidget
{
    Q_OBJECT

public:
    explicit System(Platform platform, QWidget *parent = nullptr);
    ~System();
    void setPriceManager(PricingManager *priceManager);

private slots:
    void on_pushButton_start_session_clicked();
    void startTimerBySetTime();
    void UpdateTime(qint64 Miliseconds);
    void cancelDialog();
    void startFreeTime();
    void on_pushButton_stop_resume_clicked();
    void zeroTimer();

private:
    Ui::System *ui;
    StartSessionDialog *STsession;
    Timer timer;
    PricingManager *priceManager;
    Platform platform;
    std::unordered_map<Platform, QString> PlatformToQString;
    int playerCount;
};


#endif // SYSTEM_H
