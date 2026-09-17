#ifndef MENUDIALOG_H
#define MENUDIALOG_H

#include <QDialog>
#include "extendtimedialog.h"

namespace Ui {
class MenuDialog;
}

class MenuDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MenuDialog(QWidget *parent = nullptr);
    ~MenuDialog();
    void enableExtendTime();
    void disableExtendTime();

signals:
    void cancelRequested();
    void extendTimeRequested(QTime time);

private slots:
    void on_pushButton_back_clicked();
    void on_pushButton_extend_time_clicked();
    void extendBackToMenu();
    void onExtendTime(QTime time);

private:
    Ui::MenuDialog *ui;
    ExtendTimeDialog *extendTimeDialog;
};

#endif // MENUDIALOG_H
