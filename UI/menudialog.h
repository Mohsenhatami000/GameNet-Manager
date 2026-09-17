#ifndef MENUDIALOG_H
#define MENUDIALOG_H

#include <QDialog>

namespace Ui {
class MenuDialog;
}

class MenuDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MenuDialog(QWidget *parent = nullptr);
    ~MenuDialog();

signals:
    void cancelRequested();

private slots:
    void on_pushButton_back_clicked();

private:
    Ui::MenuDialog *ui;
};

#endif // MENUDIALOG_H
