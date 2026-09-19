#ifndef EXTENDTIMEDIALOG_H
#define EXTENDTIMEDIALOG_H

#include <QDialog>
#include <QTime>

namespace Ui {
class ExtendTimeDialog;
}

class ExtendTimeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExtendTimeDialog(QWidget *parent = nullptr);
    ~ExtendTimeDialog();

signals:
    void backRequested();
    void extendTimeRequested(QTime time);

private slots:
    void on_pushButton_back_clicked();

    void on_pushButton_15Min_clicked();

    void on_pushButton_30Min_clicked();

    void on_pushButton_1Hour_clicked();

    void on_pushButton_2Hour_clicked();

    void on_pushButton_extend_clicked();

private:
    Ui::ExtendTimeDialog *ui;
    QTime time;
};

#endif // EXTENDTIMEDIALOG_H
