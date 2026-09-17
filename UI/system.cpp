#include "system.h"
#include "ui_system.h"
#include <QTime>
#include <QLocale>

System::System(Platform platform, std::unordered_map<Platform, QString> &PlatformToQString, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::System)
    , timer(this)
    , platform(platform)
    , time(0, 0)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->page);
    menuDialog = new MenuDialog(this);
    connect(menuDialog, &MenuDialog::extendTimeRequested, this, &System::extendTime);
    connect(menuDialog, &MenuDialog::cancelRequested, this, &System::cancelMenu);
    counter++;
    id = counter;
    setPlatformToString(PlatformToQString);
    Name = PlatformToQString[platform] + "-" + QString("%1").arg(id, 2, 10, QChar('0'));
    ui->label_name1->setText(Name);
    ui->label_name2->setText(Name);
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
    playerCount = STsession->getPlayerCount();
    time = STsession->getTime();
    ui->label_player_Count->setText(QString(QString::number(playerCount) + " Player(s)"));
    timer.setMode(TimerMode::countDown);
    timer.setDuration(time.msecsSinceStartOfDay());
    timer.start();
    connect(&timer, &Timer::TimeChanged, this, &System::UpdateTime);

}


void System::UpdateTime(qint64 Miliseconds){

    qint64 TimeInMinute = (Miliseconds / 1000) / 60;
    int Hours = (TimeInMinute / 60);
    int Minutes = TimeInMinute % 60;
    int Seconds = (Miliseconds / 1000) % 60;

    price = priceManager->getRule(platform, playerCount).calculateMoneyFromTime(QTime(Hours, Minutes, Seconds));

    if(timer.getMode() == TimerMode::countDown){
        qint32 totalPrice = priceManager->getRule(platform, playerCount).calculateMoneyFromTime(time);
        price = totalPrice - price;
    }

    ui->label_price->setText('$' + QLocale(QLocale::English).toString(price));
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
        ui->pushButton_stop_resume->setText("Resume");
    }
    else{
        timer.resume();
        ui->pushButton_stop_resume->setText("Stop");
    }
}

void System::startFreeTime(){

    STsession->close();
    ui->stackedWidget->setCurrentWidget(ui->page_2);
    timer.setMode(TimerMode::countUp);
    timer.start();
    playerCount = STsession->getPlayerCount();
    ui->label_player_Count->setText(QString(QString::number(playerCount) + " Player(s)"));
    connect(&timer, &Timer::TimeChanged, this, &System::UpdateTime);
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
    for(const auto& [name, item] : ItemsList){
        QString tmp = centerText(name, 35) + centerText( ('x' + QString::number(item.getQuantity())), 8) + centerText(QLocale(QLocale::English).toString(item.getProduct().getPrice()), 35) + "\n";
        ui->textBrowser_price->insertPlainText(tmp);
    }
}

void System::addProductToList(QString productName, int quantity){
    ProductItem item(productCatalog->getProduct(productName), quantity);
    addProductItem(item);
    updateProductBrowser();
    productDialog->close();
}

void System::on_pushButton_menu_clicked()
{
    menuDialog->show();
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

void System::extendTime(QTime extendTime){
    timer.extendTime(extendTime);
    QTime tmp = time.addMSecs(extendTime.msecsSinceStartOfDay());
    time.setHMS(tmp.hour(), tmp.minute(), tmp.second());
    menuDialog->close();
}