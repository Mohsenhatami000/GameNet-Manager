#ifndef CHANGEPLAYERCOUNTDIALOG_H
#define CHANGEPLAYERCOUNTDIALOG_H

#include <QDialog>

namespace Ui {
class ChangePlayerCountDialog;
}

class ChangePlayerCountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePlayerCountDialog(int playerCount, QWidget *parent = nullptr);
    ~ChangePlayerCountDialog();

signals:
    void cancelRequested();
    void playerCountChanged(int pCount);

private slots:
    void on_pushButton_cancel_clicked();
    void on_pushButton_change_clicked();

private:
    Ui::ChangePlayerCountDialog *ui;
    int playerCount;
};

#endif // CHANGEPLAYERCOUNTDIALOG_H
