#ifndef SESSIONSUMMARYDIALOG_H
#define SESSIONSUMMARYDIALOG_H

#include <QDialog>

namespace Ui {
class SessionSummaryDialog;
}

class SessionSummaryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SessionSummaryDialog(QWidget *parent = nullptr);
    void setTextBrowser(const QString html);
    ~SessionSummaryDialog();

signals:
    void endSessionRequested();
    void backToSystemRequested();

private slots:
    void on_pushButton_end_session_clicked();

    void on_pushButton_back_clicked();

private:
    Ui::SessionSummaryDialog *ui;
};

#endif // SESSIONSUMMARYDIALOG_H
