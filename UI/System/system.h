#ifndef SYSTEM_H
#define SYSTEM_H

#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QDeadlineTimer>
#include <QElapsedTimer>
#include <QMediaPlayer>
#include <QAudioOutput>

#include "UI/StartSession/startsessiondialog.h"
#include "Logic/Timer/timer.h"
#include "Logic/Price/pricingmanager.h"
#include "Logic/Product/productcatalog.h"
#include "Logic/Product/productitem.h"
#include "UI/Menu/menudialog.h"
#include "UI/Products/productsdialog.h"
#include "UI/SessionSummary/sessionsummarydialog.h"
#include "UI/TimeExpired/timeexpireddialog.h"

namespace Ui {
class System;
}

class System : public QWidget
{
    Q_OBJECT

public:
    explicit System(
        Platform platform,
        std::unordered_map<Platform, QString> &PlatformToQString,
        QWidget *parent = nullptr
        );

    ~System();

    void setPriceManager(PricingManager *priceManager);
    void setPlatformToString(
        std::unordered_map<Platform, QString> &PlatformToQString
        );
    void setProductCatalog(ProductCatalog *productCatalog);
    void addProductItem(ProductItem item);

    static int counter;

signals:
    void sessionStateChanged(bool active);

private slots:
    void on_pushButton_start_session_clicked();
    void startTimerBySetTime();
    void UpdateTime(qint64 Miliseconds);
    void cancelStartDialog();
    void startFreeTime();

    void on_pushButton_stop_resume_clicked();
    void on_pushButton_end_session_clicked(
        PrevPage prev = PrevPage::System
        );

    void zeroTimer();

    void on_pushButton_products_clicked();
    void cancelProductDialog();

    void cancelMenu();
    void addProductToList(QString productName, int quantity);
    void updateProductBrowser();

    void onExtendTime(QTime extendTime);
    void on_pushButton_menu_clicked();

    void onPlayerCountChanged(int pCount);

    void setSessionActive(bool active);

    void onEndSession();
    void endSessionBackToSystem();

    void sessionSummaryBackToExpiredTime();
    void timeExpiredEndSession();
    void timeExpiredExtendTime();

    void extendTimeBackToTimeExpired();

private:
    void addToCostSegment(int playerCount, qint64 duration);
    void finishCurrentCostSegment();

private:
    Ui::System *ui;

    StartSessionDialog *STsession = nullptr;

    Timer timer;

    QTime setDuration;

    qint64 timeInProgress = 0;

    qint64 segmentStartTime = 0;

    PricingManager *priceManager = nullptr;
    ProductCatalog *productCatalog = nullptr;

    ProductsDialog *productDialog = nullptr;
    MenuDialog *menuDialog = nullptr;
    SessionSummaryDialog *sessionSummaryDialog = nullptr;

    QMediaPlayer *mediaPlayer = nullptr;
    QAudioOutput *audioOutput = nullptr;
    TimeExpiredDialog *timeExpired = nullptr;

    std::unordered_map<QString, ProductItem> ItemsList;

    std::unordered_map<int, qint64> CostSegment;

    Platform platform;

    std::unordered_map<Platform, QString> PlatformToQString;

    int playerCount = 1;
    int id = 0;

    QString Name;

    qint32 price = 0;

    bool sessionActive = false;
};

#endif // SYSTEM_H