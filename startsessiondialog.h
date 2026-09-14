#ifndef STARTSESSIONDIALOG_H
#define STARTSESSIONDIALOG_H

#include <QDialog>
#include <QTime>


namespace Ui {
class StartSessionDialog;
}

class StartSessionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StartSessionDialog(QWidget *parent = nullptr);
    ~StartSessionDialog();
    QTime getTime() const;

signals:
    void startBySetTimeRequested();
    void cancelRequested();
    void startFreeTimeRequested();

private slots:
    void on_pushButton_set_time_clicked();

    void on_pushButton_set_price_clicked();

    void on_pushButton_free_time_clicked();

    void on_pushButton_30Min_clicked();

    void on_pushButton_1Hour_clicked();

    void on_pushButton_1_5Hour_clicked();

    void on_pushButton_2Hour_clicked();

    void on_pushButton_Start1_clicked();

    void on_pushButton_cancel1_clicked();

    void on_pushButton_cancel2_clicked();

    void on_pushButton_cancel2_2_clicked();

    void on_pushButton_start2_2_clicked();

    void on_timeEdit_time_userTimeChanged(const QTime &time);

private:
    Ui::StartSessionDialog *ui;
    QTime time;
};

#endif // STARTSESSIONDIALOG_H
