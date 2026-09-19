#ifndef SYSTEM_H
#define SYSTEM_H

#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QDeadlineTimer>
#include <QElapsedTimer>
#include "UI/StartSession/startsessiondialog.h"
#include "Logic/Timer/timer.h"
#include "Logic/Price/pricingmanager.h"
#include "Logic/Product/productcatalog.h"
#include "Logic/Product/productitem.h"
#include "UI/Menu/menudialog.h"
#include "UI/Products/productsdialog.h"
#include "UI/SessionSummary/sessionsummarydialog.h"

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

signals:
    void sessionStateChanged(bool active);

private slots:
    void on_pushButton_start_session_clicked();
    void startTimerBySetTime();
    void UpdateTime(qint64 Miliseconds);
    void cancelStartDialog();
    void startFreeTime();
    void on_pushButton_stop_resume_clicked();
    void on_pushButton_end_session_clicked();
    void zeroTimer();
    void on_pushButton_products_clicked();
    void cancelProductDialog();
    void cancelMenu();
    void addProductToList(QString productName, int quantity);
    void updateProductBrowser();
    void onExtendTime(QTime extendTime);
    void on_pushButton_menu_clicked();
    void onPlayerCountChanged(int pCount);
    void addToCostSegment(int playerCount, qint64 duration);
    void setSessionActive(bool active);
    void onEndSession();
    void endSessionBackToSystem();

private:
    Ui::System *ui;
    StartSessionDialog *STsession;
    Timer timer;
    QTime setDuration;
    qint64 timeInProgress;
    qint64 segmentStartTime;
    PricingManager *priceManager;
    ProductCatalog *productCatalog;
    ProductsDialog *productDialog;
    MenuDialog *menuDialog;
    SessionSummaryDialog *sessionSummaryDialog = nullptr;
    std::unordered_map<QString, ProductItem> ItemsList;
    std::unordered_map<int, qint64> CostSegment;
    Platform platform;
    std::unordered_map<Platform, QString> PlatformToQString;
    int playerCount;
    int id;
    QString Name;
    qint32 price;
    bool sessionActive = false;
};


#endif // SYSTEM_H
