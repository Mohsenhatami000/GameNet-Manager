#ifndef TIMER_H
#define TIMER_H

#include <QTimer>
#include <QElapsedTimer>
#include <QObject>

enum class TimerMode{
    countDown,
    countUp
};


class Timer : public QObject
{
    Q_OBJECT
private:
    QTimer *timer;
    QElapsedTimer elapsedTimer;
    QDeadlineTimer *deadLine;
    bool is_running;
    qint64 remainingTime;
    qint64 elapsedTime;
    quint64 duration;
    TimerMode mode;

private slots:
    void onTimeout();

public:
    Timer(QObject *parent = nullptr);
    ~Timer();
    void setMode(TimerMode mode);
    void setDuration(qint64 duration);
    void start();
    void stop();
    void resume();
    bool getIsRunning() const;
    TimerMode getMode() const;
signals:
    void TimeChanged(qint64 Miliseconds);
    void zeroTimerRequested();
};

#endif // TIMER_H
