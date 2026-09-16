#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include "../Logic/pricingmanager.h"
#include "../Logic/productcatalog.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    std::vector<QHBoxLayout*> horiz;
    PricingManager *priceManager;
    ProductCatalog *productCatalog;

};
#endif // MAINWINDOW_H
