#ifndef EXTENDTIMEDIALOG_H
#define EXTENDTIMEDIALOG_H

#include <QDialog>
#include <QTime>

enum class Prev{
    Menu,
    TimeExpired
};

namespace Ui {
class ExtendTimeDialog;
}

class ExtendTimeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExtendTimeDialog(Prev prev = Prev::Menu, QWidget *parent = nullptr);
    ~ExtendTimeDialog();

signals:
    void backToMenuRequested();
    void backToTimeExpiredRequested();
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
    Prev prevPage;

};

#endif // EXTENDTIMEDIALOG_H
