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
#include "../Logic/productcatalog.h"
#include "../Logic/productitem.h"
#include "menudialog.h"
#include "productsdialog.h"

namespace Ui {
class System;
}

class System : public QWidget
{
    Q_OBJECT


public:
    explicit System(Platform platform, std::unordered_map<Platform, QString> &PlatformToQString, QWidget *parent = nullptr);
    ~System();
    void setPriceManager(PricingManager *priceManager);
    static int counter;
    void setPlatformToString(std::unordered_map<Platform, QString> &PlatformToQString);
    void setProductCatalog(ProductCatalog *productCatalog);
    void addProductItem(ProductItem item);

private slots:
    void on_pushButton_start_session_clicked();
    void startTimerBySetTime();
    void UpdateTime(qint64 Miliseconds);
    void cancelStartDialog();
    void startFreeTime();
    void on_pushButton_stop_resume_clicked();
    void zeroTimer();
    void on_pushButton_products_clicked();
    void cancelProductDialog();
    void cancelMenu();
    void addProductToList(QString productName, int quantity);
    void updateProductBrowser();
    void extendTime(QTime extendTime);
    void on_pushButton_menu_clicked();

private:
    Ui::System *ui;
    StartSessionDialog *STsession;
    Timer timer;
    QTime time;
    PricingManager *priceManager;
    ProductCatalog *productCatalog;
    ProductsDialog *productDialog;
    MenuDialog *menuDialog;
    std::unordered_map<QString, ProductItem> ItemsList;
    Platform platform;
    std::unordered_map<Platform, QString> PlatformToQString;
    int playerCount;
    int id;
    QString Name;
    qint32 price;
};


#endif // SYSTEM_H
