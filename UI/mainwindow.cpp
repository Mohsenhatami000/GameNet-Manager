#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QString>
#include <QVBoxLayout>
#include "system.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGridLayout* grid = new QGridLayout(ui->page);

    for (int row = 0; row < 2; row++) {
        for (int col = 0; col < 3; col++) {
            QVBoxLayout* vertical = new QVBoxLayout();
            grid->addLayout(vertical, row, col);
            System* tmp = new System();
            vertical->addWidget(tmp);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

