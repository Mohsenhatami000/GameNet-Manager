#ifndef TIMEEXPIREDDIALOG_H
#define TIMEEXPIREDDIALOG_H

#include <QDialog>

namespace Ui {
class TimeExpiredDialog;
}

class TimeExpiredDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TimeExpiredDialog(QString msg, QWidget *parent = nullptr);
    ~TimeExpiredDialog();

signals:
    void endSessionRequested();
    void extendTimeRequested();

private slots:
    void on_pushButton_end_session_clicked();

    void on_pushButton_extend_time_clicked();

private:
    Ui::TimeExpiredDialog *ui;
};

#endif // TIMEEXPIREDDIALOG_H
