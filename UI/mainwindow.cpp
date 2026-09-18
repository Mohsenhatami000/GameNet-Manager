#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QString>
#include <QVBoxLayout>
#include "system.h"
#include <unordered_map>
#include <QDebug>
#include <QGridLayout>
#include <QSizePolicy>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("GameNet | مدیریت گیم‌نت");
    ui->menubar->hide();
    ui->statusbar->hide();

    std::unordered_map<Platform, QString> PlatformToQString;
    PlatformToQString[Platform::PC] = "PC";
    PlatformToQString[Platform::PS4] = "PS4";
    PlatformToQString[Platform::PS5] = "PS5";
    PlatformToQString[Platform::SteeringWheel] = "SW";
    PlatformToQString[Platform::VR] = "VR";

    priceManager = new PricingManager();

    QGridLayout* grid = new QGridLayout(ui->scrollAreaWidgetContents);
    grid->setContentsMargins(2, 2, 2, 2);
    grid->setHorizontalSpacing(18);
    grid->setVerticalSpacing(18);

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
            System* tmp = new System(Platform::PS4, PlatformToQString);
            tmp->setMinimumSize(340, 410);
            tmp->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

            tmp->setPriceManager(priceManager);
            tmp->setProductCatalog(productCatalog);
            grid->addWidget(tmp, row, col);
            systems.push_back(tmp);
            connect(tmp, &System::sessionStateChanged, this, [this](bool) { refreshDashboard(); });
        }
    }

    for (int column = 0; column < 3; ++column)
        grid->setColumnStretch(column, 1);

    refreshDashboard();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshDashboard()
{
    int active = 0;
    for (const auto *system : systems) {
        if (system->property("sessionActive").toBool())
            ++active;
    }

    const int available = static_cast<int>(systems.size()) - active;
    ui->activeValue->setText(QString::number(active));
    ui->freeValue->setText(QString::number(available));
    ui->totalValue->setText(QString::number(systems.size()));
}

