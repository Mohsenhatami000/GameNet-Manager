#include "sessionsummarydialog.h"
#include "UI/ui_sessionsummarydialog.h"



SessionSummaryDialog::SessionSummaryDialog(PrevPage prevPage, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SessionSummaryDialog)
    , prevPage(prevPage)
{
    ui->setupUi(this);
}

SessionSummaryDialog::~SessionSummaryDialog()
{
    delete ui;
}

void SessionSummaryDialog::on_pushButton_end_session_clicked()
{
    emit endSessionRequested();
}


void SessionSummaryDialog::setTextBrowser(const QString html){
    ui->textEdit_session_summary->setHtml(html);
}

void SessionSummaryDialog::on_pushButton_back_clicked()
{
    if(prevPage == PrevPage::System){
        emit backToSystemRequested();
        return;
    }
    emit backToTimeExpiredRequested();
}

