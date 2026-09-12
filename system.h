#ifndef SYSTEM_H
#define SYSTEM_H

#include <QWidget>
#include <QTimer>
#include <QTime>



namespace Ui {
class System;
}

class System : public QWidget
{
    Q_OBJECT

public:
    explicit System(QWidget *parent = nullptr);
    ~System();

private:
    Ui::System *ui;
    QTimer *timer;
    QTime *time;

};

#endif // SYSTEM_H
