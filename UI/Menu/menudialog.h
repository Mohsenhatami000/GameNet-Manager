#ifndef MENUDIALOG_H
#define MENUDIALOG_H

#include <QDialog>
#include "../ExtendTime/extendtimedialog.h"
#include "../Description/descriptiondialog.h"
#include "../ChangePlayerCount/changeplayercountdialog.h"

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
    void setPlayerCount(int playerCount);
    QString getDescription() const;

signals:
    void cancelRequested();
    void extendTimeRequested(QTime time);
    void playerCountChanged(int pCount);

private slots:
    void on_pushButton_back_clicked();
    void on_pushButton_extend_time_clicked();
    void extendBackToMenu();
    void onExtendTime(QTime time);
    void on_pushButton_description_clicked();
    void descriptionBackToMain();
    void on_pushButton_change_player_count_clicked();
    void changePlayerBackToMain();
    void onPlayerCount(int pCount);

private:
    Ui::MenuDialog *ui;
    ExtendTimeDialog *extendTimeDialog;
    DescriptionDialog *descriptionDialog;
    ChangePlayerCountDialog *playerCountDialog;
    int playerCount;

};

#endif // MENUDIALOG_H
