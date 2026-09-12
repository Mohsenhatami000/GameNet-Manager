#include "system.h"
#include "ui_system.h"

System::System(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::System)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    time = new QTime(0, 0);

}

System::~System()
{
    delete ui;
    delete time;
}
