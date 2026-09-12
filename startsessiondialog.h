#ifndef STARTSESSIONDIALOG_H
#define STARTSESSIONDIALOG_H

#include <QDialog>

namespace Ui {
class StartSessionDialog;
}

class StartSessionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StartSessionDialog(QWidget *parent = nullptr);
    ~StartSessionDialog();

private:
    Ui::StartSessionDialog *ui;
};

#endif // STARTSESSIONDIALOG_H
