#ifndef SESSIONSUMMARYDIALOG_H
#define SESSIONSUMMARYDIALOG_H

#include <QDialog>

enum class PrevPage{
    System,
    TimeExpired
};

namespace Ui {
class SessionSummaryDialog;
}

class SessionSummaryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SessionSummaryDialog(PrevPage prevPage = PrevPage::System, QWidget *parent = nullptr);
    void setTextBrowser(const QString html);
    ~SessionSummaryDialog();

signals:
    void endSessionRequested();
    void backToSystemRequested();
    void backToTimeExpiredRequested();

private slots:
    void on_pushButton_end_session_clicked();

    void on_pushButton_back_clicked();

private:
    Ui::SessionSummaryDialog *ui;
    PrevPage prevPage;

};

#endif // SESSIONSUMMARYDIALOG_H
