#include "system.h"
#include "ui_system.h"
#include <QTime>
#include <QLocale>
#include <QStyle>
#include "../Logic/productitem.h"

System::System(Platform platform, std::unordered_map<Platform, QString> &PlatformToQString, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::System)
    , timer(this)
    , platform(platform)
    , setDuration(0, 0)
    , segmentStartTime(0)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->page);
    connect(&timer, &Timer::zeroTimerRequested, this, &System::on_pushButton_end_session_clicked);

    menuDialog = new MenuDialog(this);
    connect(menuDialog, &MenuDialog::extendTimeRequested, this, &System::onExtendTime);
    connect(menuDialog, &MenuDialog::cancelRequested, this, &System::cancelMenu);
    connect(menuDialog, &MenuDialog::playerCountChanged, this, &System::onPlayerCountChanged);

    counter++;
    id = counter;
    setPlatformToString(PlatformToQString);
    Name = PlatformToQString[platform] + "-" + QString("%1").arg(id, 2, 10, QChar('0'));
    ui->label_name1->setText(Name);
    ui->label_name2->setText(Name);
    setSessionActive(false);
}

int System::counter = 0;

System::~System()
{
    delete ui;
}

void System::on_pushButton_start_session_clicked()
{
    STsession = new StartSessionDialog(Name, this);
    STsession->setPriceManager(priceManager);
    STsession->setPlatform(platform);
    STsession->show();
    connect(STsession, &StartSessionDialog::startBySetTimeRequested, this, &System::startTimerBySetTime);
    connect(STsession, &StartSessionDialog::cancelRequested, this, &System::cancelStartDialog);
    connect(STsession, &StartSessionDialog::startFreeTimeRequested, this, &System::startFreeTime);
    playerCount = 1;
}


void System::startTimerBySetTime(){

    STsession->close();
    ui->stackedWidget->setCurrentWidget(ui->page_2);
    setSessionActive(true);
    playerCount = STsession->getPlayerCount();
    setDuration = STsession->getTime();
    ui->label_player_Count->setText(QString::number(playerCount) + " بازیکن");
    timer.setMode(TimerMode::countDown);
    timer.setDuration(setDuration.msecsSinceStartOfDay());
    timer.start();
    connect(&timer, &Timer::TimeChanged, this, &System::UpdateTime, Qt::UniqueConnection);

}


void System::UpdateTime(qint64 Miliseconds){

    if(timer.getMode() == TimerMode::countUp){
        timeInProgress = Miliseconds;
    }
    else{
        timeInProgress = setDuration.msecsSinceStartOfDay() - Miliseconds;
    }

    qint64 TimeInMinute = (Miliseconds / 1000) / 60;
    int Hours = (TimeInMinute / 60);
    int Minutes = TimeInMinute % 60;
    int Seconds = (Miliseconds / 1000) % 60;

    price = priceManager->getRule(platform, playerCount).calculateMoneyFromTime(QTime(Hours, Minutes, Seconds).addMSecs(-segmentStartTime));

    if(timer.getMode() == TimerMode::countDown){
        qint32 totalPrice = priceManager->getRule(platform, playerCount).calculateMoneyFromTime(setDuration.addMSecs(-segmentStartTime));
        price = totalPrice - price;
    }

    ui->label_price->setText(QLocale(QLocale::English).toString(price) + " تومان");
    ui->label_price->setAlignment(Qt::AlignCenter);

    ui->label_Timer->setText(
        QString("%1:%2:%3")
            .arg(Hours, 2, 10, QChar('0'))
            .arg(Minutes, 2, 10, QChar('0'))
            .arg(Seconds, 2, 10, QChar('0'))
        );
}

void System::cancelStartDialog(){
    STsession->close();
    delete STsession;
}
void System::on_pushButton_stop_resume_clicked()
{
    if(timer.getIsRunning()){
        timer.stop();
        ui->pushButton_stop_resume->setText("ادامه");
    }
    else{
        timer.resume();
        ui->pushButton_stop_resume->setText("توقف");
    }
}

void System::on_pushButton_end_session_clicked()
{
    if (timer.getIsRunning())
        timer.stop();

    zeroTimer();
    ui->label_price->setText("۰ تومان");
    ui->textBrowser_price->setHtml("<p align='center'>محصولات افزوده‌شده در این بخش نمایش داده می‌شوند</p>");
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

void System::startFreeTime(){

    STsession->close();
    ui->stackedWidget->setCurrentWidget(ui->page_2);
    setSessionActive(true);
    timer.setMode(TimerMode::countUp);
    timer.start();
    playerCount = STsession->getPlayerCount();
    ui->label_player_Count->setText(QString::number(playerCount) + " بازیکن");
    connect(&timer, &Timer::TimeChanged, this, &System::UpdateTime, Qt::UniqueConnection);
}

void System::zeroTimer(){
    ui->label_Timer->setText("00:00:00");
}


void System::setPriceManager(PricingManager *priceManager){
    this->priceManager = priceManager;
}

void System::setPlatformToString(std::unordered_map<Platform, QString> &PlatformToQString){
    for(auto &i : PlatformToQString){
        this->PlatformToQString[i.first] = i.second;
    }
}

void System::setProductCatalog(ProductCatalog *productCatalog){
    this->productCatalog = productCatalog;
}

void System::on_pushButton_products_clicked()
{
    productDialog = new ProductsDialog(productCatalog, this);
    productDialog->show();
    connect(productDialog, &ProductsDialog::cancelRequested, this, &System::cancelProductDialog);
    connect(productDialog, &ProductsDialog::addProductRequested, this, &System::addProductToList);
}

void System::cancelProductDialog(){
    productDialog->close();
    delete productDialog;
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

void System::addProductItem(ProductItem item){
    if(ItemsList.count(item.getProduct().getName())){
        ItemsList[item.getProduct().getName()] += item;
        return;
    }
    ItemsList[item.getProduct().getName()] = item;
}

void System::updateProductBrowser(){

    ui->textBrowser_price->clear();
    QString html = R"(
                        <table width="100%" cellspacing="0" cellpadding="4">
                    )";

    QTime durationQTime;

    for(const auto& [name, item] : ItemsList){

        html += "<tr>";

        html += "<td align=\"center\">" +
                name +
                "</td>";

        html += "<td align=\"center\">x" +
                QString::number(item.getQuantity()) +
                "</td>";

        html += "<td align=\"center\">" +
                QLocale(QLocale::English).toString(
                    item.getProduct().getPrice()
                    ) +
                "</td>";

        html += "</tr>";
    }

    for(const auto& [pCount, duration] : CostSegment){
        durationQTime = durationQTime.fromMSecsSinceStartOfDay(duration);
        qint32 totalPrice = priceManager->getRule(platform, pCount).calculateMoneyFromTime(durationQTime);

        html += "<tr>";

        html += "<td align=\"center\">" +
                durationQTime.toString("hh:mm:ss") +
                "</td>";

        html += "<td align=\"center\">x" +
                QString::number(pCount) +
                "</td>";

        html += "<td align=\"center\">" +
                QLocale(QLocale::English).toString(
                    totalPrice) +
                "</td>";

        html += "</tr>";
    }
    ui->textBrowser_price->setHtml(html);
}

void System::addProductToList(QString productName, int quantity){
    ProductItem item(productCatalog->getProduct(productName), quantity);
    addProductItem(item);
    updateProductBrowser();
    productDialog->close();
}

void System::setSessionActive(bool active)
{
    sessionActive = active;
    setProperty("sessionActive", active);
    ui->stationCard->setProperty("active", active);
    ui->stationCard->style()->unpolish(ui->stationCard);
    ui->stationCard->style()->polish(ui->stationCard);
    emit sessionStateChanged(active);
}

void System::on_pushButton_menu_clicked()
{
    menuDialog->show();
    menuDialog->setPlayerCount(playerCount);
    if(timer.getMode() == TimerMode::countUp){
        menuDialog->disableExtendTime();
    }
    else{
        menuDialog->enableExtendTime();
    }
}

void System::cancelMenu(){
    menuDialog->close();
}

void System::onExtendTime(QTime extendTime){
    timer.extendTime(extendTime);
    QTime tmp = setDuration.addMSecs(extendTime.msecsSinceStartOfDay());
    setDuration.setHMS(tmp.hour(), tmp.minute(), tmp.second());
    menuDialog->close();
}

void System::addToCostSegment(int playerCount, qint64 duration){
    if(!CostSegment.count(playerCount)){
        CostSegment[playerCount] = duration;
        return;
    }
    CostSegment[playerCount] += duration;
}

void System::onPlayerCountChanged(int pCount){
    cancelMenu();
    ui->label_player_Count->setText(QString::number(pCount) + " بازیکن");
    segmentStartTime = timeInProgress;
    addToCostSegment(playerCount, timeInProgress);
    playerCount = pCount;
    setDuration = QTime::fromMSecsSinceStartOfDay(setDuration.msecsSinceStartOfDay() - timeInProgress);
    updateProductBrowser();
}


