#ifndef DESCRIPTIONDIALOG_H
#define DESCRIPTIONDIALOG_H

#include <QDialog>

namespace Ui {
class DescriptionDialog;
}

class DescriptionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DescriptionDialog(QWidget *parent = nullptr);
    ~DescriptionDialog();
    QString getDescription() const;

signals:
    void backToMainRequested();

private slots:
    void on_pushButton_close_clicked();

private:
    Ui::DescriptionDialog *ui;
};

#endif // DESCRIPTIONDIALOG_H
