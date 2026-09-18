#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QString>
#include <QVBoxLayout>
#include "system.h"
#include <unordered_map>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    std::unordered_map<Platform, QString> PlatformToQString;
    PlatformToQString[Platform::PC] = "PC";
    PlatformToQString[Platform::PS4] = "PS4";
    PlatformToQString[Platform::PS5] = "PS5";
    PlatformToQString[Platform::SteeringWheel] = "SW";
    PlatformToQString[Platform::VR] = "VR";

    priceManager = new PricingManager();

    QGridLayout* grid = new QGridLayout(ui->scrollAreaWidgetContents);

    priceManager->addPricingRule(PricingRule(Platform::PS4, 1, 45000));
    priceManager->addPricingRule(PricingRule(Platform::PS4, 2, 80000));
    priceManager->addPricingRule(PricingRule(Platform::PS4, 3, 120000));
    priceManager->addPricingRule(PricingRule(Platform::PS4, 4, 160000));
    priceManager->addPricingRule(PricingRule(Platform::PC, 1, 45000));
    priceManager->addPricingRule(PricingRule(Platform::SteeringWheel, 1, 70000));
    priceManager->addPricingRule(PricingRule(Platform::VR, 1, 100000));

    priceManager->addPricingRule(PricingRule(Platform::PS4, 1, 45000));
    priceManager->addPricingRule(PricingRule(Platform::PS4, 2, 80000));
    priceManager->addPricingRule(PricingRule(Platform::PS4, 3, 120000));
    priceManager->addPricingRule(PricingRule(Platform::PS4, 4, 160000));

    productCatalog = new ProductCatalog();
    productCatalog->addProduct(Product(QString("Cake"), 35000));
    productCatalog->addProduct(Product(QString("Juice"), 58000));
    productCatalog->addProduct(Product(QString("Biscuit"), 55000));


    for (int row = 0; row < 2; row++) {
        for (int col = 0; col < 3; col++) {
            QVBoxLayout* vertical = new QVBoxLayout();
            grid->addLayout(vertical, row, col);

            System* tmp = new System(Platform::PS4, PlatformToQString);
            tmp->setMinimumSize(300, 400);

            tmp->setPriceManager(priceManager);
            tmp->setProductCatalog(productCatalog);
            vertical->addWidget(tmp);
        }
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}

