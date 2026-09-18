#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <vector>
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
    void refreshDashboard();

    Ui::MainWindow *ui;
    std::vector<QHBoxLayout*> horiz;
    std::vector<class System*> systems;
    PricingManager *priceManager;
    ProductCatalog *productCatalog;

};
#endif // MAINWINDOW_H
