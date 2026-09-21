#include "system.h"
#include "ui_system.h"

#include <QTime>
#include <QLocale>
#include <QStyle>

#include "Logic/Product/productitem.h"


System::System(
    Platform platform,
    std::unordered_map<Platform, QString> &PlatformToQString,
    QWidget *parent
    )
    : QWidget(parent)
    , ui(new Ui::System)
    , timer(this)
    , platform(platform)
    , setDuration(0, 0)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentWidget(ui->page);

    ui->stationIcon->setText(PlatformToQString[platform]);

    if (platform == Platform::PS4 || platform == Platform::PS5) {
        ui->platformBadge->setText("PLAYSTATION");
    }
    else if (platform == Platform::PC) {
        ui->platformBadge->setText("COMPUTER");
    }
    else if (platform == Platform::SteeringWheel) {
        ui->platformBadge->setText("STEERING WHEEL");
    }
    else if (platform == Platform::VR) {
        ui->platformBadge->setText("VIRTUAL REALITY");
    }

    connect(
        &timer,
        &Timer::zeroTimerRequested,
        this,
        &System::zeroTimer
        );

    menuDialog = new MenuDialog(this);

    connect(
        menuDialog,
        &MenuDialog::extendTimeRequested,
        this,
        &System::onExtendTime
        );

    connect(
        menuDialog,
        &MenuDialog::cancelRequested,
        this,
        &System::cancelMenu
        );

    connect(
        menuDialog,
        &MenuDialog::playerCountChanged,
        this,
        &System::onPlayerCountChanged
        );

    connect(
        menuDialog,
        &MenuDialog::backToTimeExpiredRequested,
        this,
        &System::extendTimeBackToTimeExpired
        );

    counter++;
    id = counter;

    setPlatformToString(PlatformToQString);

    Name = PlatformToQString[platform]
           + "-"
           + QString("%1").arg(id, 2, 10, QChar('0'));

    ui->label_name1->setText(Name);
    ui->label_name2->setText(Name);

    setSessionActive(false);
}


int System::counter = 0;


System::~System()
{
    delete ui;
}

void System::extendTimeBackToTimeExpired(){
    timeExpired->show();
}

void System::on_pushButton_start_session_clicked()
{
    STsession = new StartSessionDialog(Name, this);

    STsession->setPriceManager(priceManager);
    STsession->setPlatform(platform);

    STsession->show();

    connect(
        STsession,
        &StartSessionDialog::startBySetTimeRequested,
        this,
        &System::startTimerBySetTime
        );

    connect(
        STsession,
        &StartSessionDialog::cancelRequested,
        this,
        &System::cancelStartDialog
        );

    connect(
        STsession,
        &StartSessionDialog::startFreeTimeRequested,
        this,
        &System::startFreeTime
        );

    playerCount = 1;
}


void System::startTimerBySetTime()
{
    STsession->close();

    ui->stackedWidget->setCurrentWidget(ui->page_2);

    setSessionActive(true);

    playerCount = STsession->getPlayerCount();

    setDuration = STsession->getTime();

    timeInProgress = 0;
    segmentStartTime = 0;
    CostSegment.clear();

    ui->label_player_Count->setText(
        QString::number(playerCount) + " بازیکن"
        );

    timer.setMode(TimerMode::countDown);

    timer.setDuration(
        setDuration.msecsSinceStartOfDay()
        );

    timer.start();

    connect(
        &timer,
        &Timer::TimeChanged,
        this,
        &System::UpdateTime,
        Qt::UniqueConnection
        );
}


void System::startFreeTime()
{
    STsession->close();

    ui->stackedWidget->setCurrentWidget(ui->page_2);

    setSessionActive(true);

    playerCount = STsession->getPlayerCount();

    timeInProgress = 0;
    segmentStartTime = 0;
    CostSegment.clear();

    timer.setMode(TimerMode::countUp);
    timer.start();

    ui->label_player_Count->setText(
        QString::number(playerCount) + " بازیکن"
        );

    connect(
        &timer,
        &Timer::TimeChanged,
        this,
        &System::UpdateTime,
        Qt::UniqueConnection
        );
}


void System::UpdateTime(qint64 Miliseconds)
{

    if (timer.getMode() == TimerMode::countUp) {
        timeInProgress = Miliseconds;
    }
    else {
        timeInProgress =
            setDuration.msecsSinceStartOfDay() - Miliseconds;
    }

    if (timeInProgress < 0)
        timeInProgress = 0;

    qint64 TimeInMinute = (Miliseconds / 1000) / 60;

    int Hours = static_cast<int>(TimeInMinute / 60);
    int Minutes = static_cast<int>(TimeInMinute % 60);
    int Seconds = static_cast<int>((Miliseconds / 1000) % 60);

    qint64 currentSegmentDuration =
        timeInProgress - segmentStartTime;

    if (currentSegmentDuration < 0)
        currentSegmentDuration = 0;

    QTime currentSegmentTime =
        QTime::fromMSecsSinceStartOfDay(currentSegmentDuration);

    price =
        priceManager
            ->getRule(platform, playerCount)
            .calculateMoneyFromTime(currentSegmentTime);

    ui->label_price->setText(
        QLocale(QLocale::English).toString(price)
        + " تومان"
        );

    ui->label_price->setAlignment(Qt::AlignCenter);

    ui->label_Timer->setText(
        QString("%1:%2:%3")
            .arg(Hours, 2, 10, QChar('0'))
            .arg(Minutes, 2, 10, QChar('0'))
            .arg(Seconds, 2, 10, QChar('0'))
        );
}


void System::cancelStartDialog()
{
    STsession->close();

    delete STsession;
    STsession = nullptr;
}


void System::on_pushButton_stop_resume_clicked()
{
    if (timer.getIsRunning()) {
        timer.stop();

        ui->pushButton_stop_resume->setText("ادامه");
    }
    else {
        timer.resume();

        ui->pushButton_stop_resume->setText("توقف");
    }
}


void System::sessionSummaryBackToExpiredTime()
{
    timeExpired->show();
    sessionSummaryDialog->close();

    delete sessionSummaryDialog;
    sessionSummaryDialog = nullptr;
}


void System::onPushButtonEndSessionClicked(PrevPage prev)
{
    finishCurrentCostSegment();

    if (!sessionSummaryDialog) {
        sessionSummaryDialog = new SessionSummaryDialog(prev, this);

        sessionSummaryDialog->show();

        connect(
            sessionSummaryDialog,
            &SessionSummaryDialog::endSessionRequested,
            this,
            &System::onEndSession
            );

        connect(
            sessionSummaryDialog,
            &SessionSummaryDialog::backToSystemRequested,
            this,
            &System::endSessionBackToSystem
            );

        connect(
            sessionSummaryDialog,
            &SessionSummaryDialog::backToTimeExpiredRequested,
            this,
            &System::sessionSummaryBackToExpiredTime
            );
    }

    QString html = R"(
        <table width="100%" cellspacing="0" cellpadding="4">
    )";

    QTime durationQTime;

    qint32 SumPrice = 0;
    qint32 SumProducts = 0;
    qint32 SumTimeCosts = 0;

    html += "<tr> <td align=\"center\"> </td> </tr>";

    for (const auto& [name, item] : ItemsList) {

        SumProducts +=
            item.getProduct().getPrice() * item.getQuantity();

        html += "<tr>";

        html +=
            "<td align=\"center\">" +
            name +
            "</td>";

        html +=
            "<td align=\"center\">x" +
            QString::number(item.getQuantity()) +
            "</td>";

        html +=
            "<td align=\"center\">" +
            QLocale(QLocale::English).toString(
                item.getProduct().getPrice()
                ) +
            " تومان" +
            "</td>";

        html += "</tr>";
    }

    for (const auto& [pCount, duration] : CostSegment) {

        durationQTime =
            QTime::fromMSecsSinceStartOfDay(duration);

        qint32 totalPrice =
            priceManager
                ->getRule(platform, pCount)
                .calculateMoneyFromTime(durationQTime);

        SumTimeCosts += totalPrice;

        html += "<tr>";

        html +=
            "<td align=\"center\">" +
            durationQTime.toString("hh:mm:ss") +
            "</td>";

        html +=
            "<td align=\"center\">" +
            QString::number(pCount) +
            " نفره" +
            "</td>";

        html +=
            "<td align=\"center\">" +
            QLocale(QLocale::English).toString(totalPrice) +
            " تومان" +
            "</td>";

        html += "</tr>";
    }

    SumPrice += SumProducts + SumTimeCosts;

    html +=
        "<tr> <td> <hr> </td> <td> <hr> </td> <td> <hr> </td> </tr>";

    html += "<tr>";

    html +=
        "<td align=\"center\">" +
        QString(": مجموع هزینه بازی") +
        "</td>";

    html += "<td> </td>";

    html +=
        "<td align=\"center\">" +
        QLocale(QLocale::English).toString(SumTimeCosts) +
        " تومان" +
        "</td>";

    html += "</tr>";

    html += "<tr>";

    html +=
        "<td align=\"center\">" +
        QString(": مجموع هزینه کالا ها") +
        "</td>";

    html += "<td> </td>";

    html +=
        "<td align=\"center\">" +
        QLocale(QLocale::English).toString(SumProducts) +
        " تومان" +
        "</td>";

    html += "</tr>";

    html +=
        "<tr> <td> <hr> </td> <td> <hr> </td> <td> <hr> </td> </tr>";

    html += "<tr>";

    html +=
        "<td align=\"center\">" +
        QString(": مبلغ قابل پرداخت") +
        "</td>";

    html += "<td> </td>";

    html +=
        "<td align=\"center\">" +
        QLocale(QLocale::English).toString(SumPrice) +
        " تومان" +
        "</td>";

    html += "</tr>";

    html += "<br>";

    html +=
        "<tr> <td> </td> "
        "<td align=\"center\">توضیحات :</td> "
        "<td> </td></tr>";

    html += "<br>";

    html += "<div style=\"white-space: pre-line;\">";

    html += menuDialog->getDescription();

    html += "</div>";

    sessionSummaryDialog->setTextBrowser(html);
}


void System::onEndSession()
{
    if (timer.getIsRunning())
        timer.stop();

    delete sessionSummaryDialog;
    sessionSummaryDialog = nullptr;

    ui->label_Timer->setText("00:00:00");
    ui->label_price->setText("۰ تومان");

    ui->textBrowser_price->setHtml(
        "<p align='center'>"
        "محصولات افزوده‌شده در این بخش نمایش داده می‌شوند"
        "</p>"
        );

    ui->pushButton_stop_resume->setText("توقف");

    ItemsList.clear();
    CostSegment.clear();

    setDuration = QTime(0, 0);

    timeInProgress = 0;
    segmentStartTime = 0;

    price = 0;

    ui->stackedWidget->setCurrentWidget(ui->page);

    setSessionActive(false);
}

void System::timeExpiredExtendTime(){

    mediaPlayer->stop();
    timeExpired->close();
    menuDialog->onPushButtonExtendTimeClicked(Prev::TimeExpired);
}

void System::zeroTimer()
{

    timeInProgress =
        setDuration.msecsSinceStartOfDay();

    finishCurrentCostSegment();

    timeExpired =
        new TimeExpiredDialog(
            QString("زمان سیستم ") +
                Name +
                QString(" به پایان رسید."),
            this
            );

    timeExpired->show();

    connect(
        timeExpired,
        &TimeExpiredDialog::endSessionRequested,
        this,
        &System::timeExpiredEndSession
        );

    connect(
        timeExpired,
        &TimeExpiredDialog::extendTimeRequested,
        this,
        &System::timeExpiredExtendTime);

    ui->label_Timer->setText("00:00:00");

    mediaPlayer = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);

    mediaPlayer->setAudioOutput(audioOutput);

    mediaPlayer->setSource(
        QUrl("qrc:/sounds/alarm.mp3")
        );

    audioOutput->setVolume(1);

    mediaPlayer->play();

    mediaPlayer->setLoops(-1);
}


void System::timeExpiredEndSession()
{
    mediaPlayer->stop();
    timeExpired->close();

    onPushButtonEndSessionClicked(
        PrevPage::TimeExpired
        );
}


void System::setPriceManager(PricingManager *priceManager)
{
    this->priceManager = priceManager;
}


void System::setPlatformToString(
    std::unordered_map<Platform, QString> &PlatformToQString
    )
{
    for (auto &i : PlatformToQString) {
        this->PlatformToQString[i.first] = i.second;
    }
}


void System::setProductCatalog(ProductCatalog *productCatalog)
{
    this->productCatalog = productCatalog;
}


void System::on_pushButton_products_clicked()
{
    productDialog =
        new ProductsDialog(productCatalog, this);

    productDialog->show();

    connect(
        productDialog,
        &ProductsDialog::cancelRequested,
        this,
        &System::cancelProductDialog
        );

    connect(
        productDialog,
        &ProductsDialog::addProductRequested,
        this,
        &System::addProductToList
        );
}


void System::cancelProductDialog()
{
    productDialog->close();

    delete productDialog;
    productDialog = nullptr;
}


QString centerText(const QString& text, int width)
{
    int totalPadding = width - text.length();

    if (totalPadding <= 0)
        return text;

    int leftPadding = totalPadding / 2;
    int rightPadding = totalPadding - leftPadding;

    return QString(leftPadding, ' ')
           + text
           + QString(rightPadding, ' ');
}


void System::addProductItem(ProductItem item)
{
    if (ItemsList.count(item.getProduct().getName())) {

        ItemsList[item.getProduct().getName()] += item;

        return;
    }

    ItemsList[item.getProduct().getName()] = item;
}


void System::updateProductBrowser()
{
    QString html = R"(
        <table width="100%" cellspacing="0" cellpadding="4">
    )";

    QTime durationQTime;

    for (const auto& [name, item] : ItemsList) {

        html += "<tr>";

        html +=
            "<td align=\"center\">" +
            name +
            "</td>";

        html +=
            "<td align=\"center\">x" +
            QString::number(item.getQuantity()) +
            "</td>";

        html +=
            "<td align=\"center\">" +
            QLocale(QLocale::English).toString(
                item.getProduct().getPrice()
                ) +
            " تومن" +
            "</td>";

        html += "</tr>";
    }

    for (const auto& [pCount, duration] : CostSegment) {

        durationQTime =
            QTime::fromMSecsSinceStartOfDay(duration);

        qint32 totalPrice =
            priceManager
                ->getRule(platform, pCount)
                .calculateMoneyFromTime(durationQTime);

        html += "<tr>";

        html +=
            "<td align=\"center\">" +
            durationQTime.toString("hh:mm:ss") +
            "</td>";

        html +=
            "<td align=\"center\">" +
            QString::number(pCount) +
            " نفره" +
            "</td>";

        html +=
            "<td align=\"center\">" +
            QLocale(QLocale::English).toString(totalPrice) +
            " تومن" +
            "</td>";

        html += "</tr>";
    }

    ui->textBrowser_price->setHtml(html);
}


void System::addProductToList(
    QString productName,
    int quantity
    )
{
    ProductItem item(
        productCatalog->getProduct(productName),
        quantity
        );

    addProductItem(item);

    updateProductBrowser();

    productDialog->close();
}


void System::setSessionActive(bool active)
{
    sessionActive = active;

    setProperty("sessionActive", active);

    ui->stationCard->setProperty(
        "active",
        active
        );

    ui->stationCard->style()->unpolish(
        ui->stationCard
        );

    ui->stationCard->style()->polish(
        ui->stationCard
        );

    emit sessionStateChanged(active);
}


void System::on_pushButton_menu_clicked()
{
    menuDialog->show();

    menuDialog->setPlayerCount(playerCount);

    if (timer.getMode() == TimerMode::countUp) {
        menuDialog->disableExtendTime();
    }
    else {
        menuDialog->enableExtendTime();
    }
}


void System::cancelMenu()
{
    menuDialog->close();
}


void System::onExtendTime(QTime extendTime)
{
    timer.extendTime(extendTime);

    QTime tmp =
        setDuration.addMSecs(
            extendTime.msecsSinceStartOfDay()
            );

    setDuration.setHMS(
        tmp.hour(),
        tmp.minute(),
        tmp.second()
        );

    menuDialog->close();
}


void System::addToCostSegment(
    int playerCount,
    qint64 duration
    )
{
    if (duration <= 0)
        return;

    if (!CostSegment.count(playerCount)) {
        CostSegment[playerCount] = duration;
        return;
    }

    CostSegment[playerCount] += duration;
}


void System::finishCurrentCostSegment()
{

    qint64 duration =
        timeInProgress - segmentStartTime;

    if (duration <= 0)
        return;

    addToCostSegment(
        playerCount,
        duration
        );

    segmentStartTime = timeInProgress;
}


void System::onPlayerCountChanged(int pCount)
{
    cancelMenu();

    if (pCount == playerCount)
        return;

    finishCurrentCostSegment();

    playerCount = pCount;

    segmentStartTime = timeInProgress;

    ui->label_player_Count->setText(
        QString::number(playerCount) +
        " بازیکن"
        );

    updateProductBrowser();
}


void System::endSessionBackToSystem()
{
    sessionSummaryDialog->close();

    delete sessionSummaryDialog;
    sessionSummaryDialog = nullptr;
}