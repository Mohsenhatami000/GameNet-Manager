#include "UI/mainwindow.h"

#include <QApplication>
#include <QFont>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setFont(QFont("Segoe UI", 10));
    a.setStyleSheet(R"(
        QMainWindow { background: #0b1020; }
        QWidget#centralwidget { background: #0b1020; }
        QScrollArea, QScrollArea > QWidget > QWidget { border: 0; background: transparent; }
        QScrollBar:vertical { background: transparent; width: 8px; margin: 4px; }
        QScrollBar::handle:vertical { background: #2c3858; min-height: 32px; border-radius: 4px; }

        QFrame#topBar { background: #141c31; border: 1px solid #26324d; border-radius: 16px; }
        QLabel#brandMark { color: #ffffff; background: #6d5dfc; border-radius: 14px; font: 800 14pt "Segoe UI"; }
        QLabel#appTitle { color: #f8fafc; font: 800 20pt "Segoe UI"; }
        QLabel#appSubtitle, QLabel#todayLabel { color: #8f9bb3; font: 10pt "Segoe UI"; }
        QLabel#liveStatus { color: #62e6a7; font: 700 10pt "Segoe UI"; }

        QFrame#summaryActive, QFrame#summaryFree, QFrame#summaryTotal { min-height: 82px; border-radius: 14px; }
        QFrame#summaryActive { background: #242042; border: 1px solid #474078; }
        QFrame#summaryFree { background: #102b2b; border: 1px solid #245353; }
        QFrame#summaryTotal { background: #18233b; border: 1px solid #33466a; }
        QLabel#activeValue, QLabel#freeValue, QLabel#totalValue { color: #ffffff; font: 800 22pt "Segoe UI"; }
        QLabel#activeCaption, QLabel#freeCaption, QLabel#totalCaption { color: #aeb9cc; font: 600 9pt "Segoe UI"; }
        QLabel#sectionTitle { color: #f4f7fc; font: 800 16pt "Segoe UI"; }
        QLabel#sectionHint { color: #8491aa; font: 10pt "Segoe UI"; }

        QFrame#stationCard { background: #141c31; border: 1px solid #26324d; border-radius: 16px; }
        QFrame#stationCard[active="true"] { border: 1px solid #7368ff; background: #171e38; }
        QStackedWidget#stackedWidget, QStackedWidget#stackedWidget > QWidget { background: transparent; border: 0; }
        QLabel#platformBadge { color: #afbbcf; background: #202b45; border-radius: 8px; padding: 5px 8px; font: 700 8pt "Segoe UI"; }
        QLabel#label_free, QLabel#label_in_use { color: #65e6a5; background: #183a35; border-radius: 8px; padding: 5px 8px; font: 700 9pt "Segoe UI"; }
        QLabel#label_in_use { color: #b9b2ff; background: #2b2750; }
        QLabel#stationIcon { color: #ffffff; background: #2a2754; border: 1px solid #4f49a3; border-radius: 34px; min-width: 68px; max-width: 68px; min-height: 68px; max-height: 68px; margin-left: auto; margin-right: auto; font: 800 22pt "Segoe UI"; }
        QLabel#label_name1 { color: #f7f8fc; font: 800 19pt "Segoe UI"; }
        QLabel#availableDescription, QLabel#timerCaption { color: #8592ab; font: 10pt "Segoe UI"; }
        QLabel#label_name2 { color: #f7f8fc; font: 800 14pt "Segoe UI"; }
        QLabel#label_Timer { color: #ffffff; font: 800 28pt "Consolas"; letter-spacing: 2px; }
        QLabel#label_player_Count, QLabel#label_price { color: #b9c3d6; background: #1d2840; border-radius: 9px; padding: 8px 10px; font: 700 10pt "Segoe UI"; }
        QLabel#label_price { color: #86f0c2; }
        QTextBrowser#textBrowser_price { color: #91a0ba; background: #10182a; border: 1px solid #26324d; border-radius: 9px; padding: 5px; font: 9pt "Segoe UI"; }

        QPushButton { color: #dce4f4; background: #202b45; border: 1px solid #34415e; border-radius: 9px; padding: 9px 12px; font: 700 10pt "Segoe UI"; }
        QPushButton:hover { color: #ffffff; background: #2b3857; border-color: #536483; }
        QPushButton:pressed { background: #172137; }
        QPushButton:disabled { color: #6c778e; background: #171e2d; border-color: #243047; }
        QPushButton#pushButton_start_session { color: #ffffff; background: #6d5dfc; border: 1px solid #8175ff; font: 800 11pt "Segoe UI"; }
        QPushButton#pushButton_start_session:hover { background: #7c70ff; }
        QPushButton#pushButton_end_session { color: #ffbec7; background: #382335; border-color: #744258; }
        QPushButton#pushButton_end_session:hover { color: #ffffff; background: #523047; }

        QDialog { background: #141c31; color: #e8edf8; }
        QDialog QLabel { color: #e8edf8; }
        QLineEdit, QTimeEdit, QSpinBox, QComboBox, QTextEdit { color: #eff4ff; background: #10182a; border: 1px solid #34415e; border-radius: 8px; padding: 7px 9px; min-height: 22px; selection-background-color: #6d5dfc; }
        QLineEdit:focus, QTimeEdit:focus, QSpinBox:focus, QComboBox:focus, QTextEdit:focus { border-color: #8175ff; }
        QComboBox::drop-down, QSpinBox::up-button, QSpinBox::down-button, QTimeEdit::up-button, QTimeEdit::down-button { border: 0; width: 22px; }
        QComboBox QAbstractItemView { color: #eff4ff; background: #1b2640; border: 1px solid #45557a; selection-background-color: #6d5dfc; }
        QMessageBox { background: #141c31; }
        QLabel#label_titr, QLabel#productTitle, QLabel#menuTitle, QLabel#extendTitle,
        QLabel#label_change_player_count, QLabel#label_description { color: #ffffff; font: 800 17pt "Segoe UI"; }
        QLabel#label_calculate_type, QLabel#productSubtitle, QLabel#menuSubtitle,
        QLabel#changePlayerHint, QLabel#descriptionHint, QLabel#welcomeText { color: #8f9bb3; font: 10pt "Segoe UI"; }
        QLabel#welcomeIcon { color: #c8c4ff; background: #2b2750; border: 1px solid #4f49a3; border-radius: 30px; min-width: 60px; max-width: 60px; min-height: 60px; max-height: 60px; margin-left: auto; margin-right: auto; font: 800 21pt "Segoe UI"; }
        QLabel#welcomeTitle, QLabel#freeTitle { color: #f3f5ff; font: 800 14pt "Segoe UI"; }
        QLabel#label_show_time { color: #ffffff; background: #10182a; border: 1px solid #34415e; border-radius: 10px; font: 800 21pt "Consolas"; }
        QDialog QPushButton#pushButton_Start1, QDialog QPushButton#pushButton_start2,
        QDialog QPushButton#pushButton_start2_2, QDialog QPushButton#pushButton_add,
        QDialog QPushButton#pushButton_extend, QDialog QPushButton#pushButton_change { color: #ffffff; background: #6d5dfc; border-color: #8175ff; }
        QDialog QPushButton#pushButton_Start1:hover, QDialog QPushButton#pushButton_start2:hover,
        QDialog QPushButton#pushButton_start2_2:hover, QDialog QPushButton#pushButton_add:hover,
        QDialog QPushButton#pushButton_extend:hover, QDialog QPushButton#pushButton_change:hover { background: #7c70ff; }
    )");
    MainWindow w;
    w.show();


    return QApplication::exec();
}
