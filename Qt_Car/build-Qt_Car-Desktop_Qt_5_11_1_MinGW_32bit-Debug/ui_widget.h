/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QComboBox *comboBox_COM;
    QPushButton *pushButton_Open;
    QPushButton *pushButton_Auto;
    QPushButton *pushButton_;
    QPushButton *pushButton_UnAUto;
    QPushButton *pushButton_go;
    QPushButton *pushButton_left;
    QPushButton *pushButton_right;
    QPushButton *pushButton_back;
    QLabel *label_Logo;
    QLabel *label_Pic;
    QTextEdit *textEdit_Msg;
    QPushButton *pushButton_Update;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(800, 504);
        Widget->setStyleSheet(QStringLiteral("color: rgb(0, 170, 255);"));
        comboBox_COM = new QComboBox(Widget);
        comboBox_COM->setObjectName(QStringLiteral("comboBox_COM"));
        comboBox_COM->setGeometry(QRect(30, 30, 141, 51));
        pushButton_Open = new QPushButton(Widget);
        pushButton_Open->setObjectName(QStringLiteral("pushButton_Open"));
        pushButton_Open->setGeometry(QRect(190, 30, 71, 51));
        pushButton_Auto = new QPushButton(Widget);
        pushButton_Auto->setObjectName(QStringLiteral("pushButton_Auto"));
        pushButton_Auto->setGeometry(QRect(30, 110, 71, 41));
        pushButton_ = new QPushButton(Widget);
        pushButton_->setObjectName(QStringLiteral("pushButton_"));
        pushButton_->setGeometry(QRect(120, 110, 71, 41));
        pushButton_UnAUto = new QPushButton(Widget);
        pushButton_UnAUto->setObjectName(QStringLiteral("pushButton_UnAUto"));
        pushButton_UnAUto->setGeometry(QRect(210, 110, 71, 41));
        pushButton_go = new QPushButton(Widget);
        pushButton_go->setObjectName(QStringLiteral("pushButton_go"));
        pushButton_go->setGeometry(QRect(100, 280, 93, 51));
        pushButton_left = new QPushButton(Widget);
        pushButton_left->setObjectName(QStringLiteral("pushButton_left"));
        pushButton_left->setGeometry(QRect(20, 350, 93, 51));
        pushButton_right = new QPushButton(Widget);
        pushButton_right->setObjectName(QStringLiteral("pushButton_right"));
        pushButton_right->setGeometry(QRect(180, 350, 93, 51));
        pushButton_back = new QPushButton(Widget);
        pushButton_back->setObjectName(QStringLiteral("pushButton_back"));
        pushButton_back->setGeometry(QRect(100, 420, 93, 51));
        label_Logo = new QLabel(Widget);
        label_Logo->setObjectName(QStringLiteral("label_Logo"));
        label_Logo->setGeometry(QRect(570, 30, 201, 61));
        label_Pic = new QLabel(Widget);
        label_Pic->setObjectName(QStringLiteral("label_Pic"));
        label_Pic->setGeometry(QRect(480, 110, 281, 241));
        textEdit_Msg = new QTextEdit(Widget);
        textEdit_Msg->setObjectName(QStringLiteral("textEdit_Msg"));
        textEdit_Msg->setGeometry(QRect(460, 380, 311, 87));
        pushButton_Update = new QPushButton(Widget);
        pushButton_Update->setObjectName(QStringLiteral("pushButton_Update"));
        pushButton_Update->setGeometry(QRect(280, 30, 61, 51));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        pushButton_Open->setText(QApplication::translate("Widget", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        pushButton_Auto->setText(QApplication::translate("Widget", "\345\267\241\346\243\200", nullptr));
        pushButton_->setText(QApplication::translate("Widget", "\351\201\277\351\232\234", nullptr));
        pushButton_UnAUto->setText(QApplication::translate("Widget", "\346\211\213\345\212\250", nullptr));
        pushButton_go->setText(QApplication::translate("Widget", "\345\211\215\350\277\233", nullptr));
        pushButton_left->setText(QApplication::translate("Widget", "\345\267\246\350\275\254", nullptr));
        pushButton_right->setText(QApplication::translate("Widget", "\345\217\263\350\275\254", nullptr));
        pushButton_back->setText(QApplication::translate("Widget", "\345\220\216\351\200\200", nullptr));
        label_Logo->setText(QApplication::translate("Widget", "logo", nullptr));
        label_Pic->setText(QApplication::translate("Widget", "pic", nullptr));
        pushButton_Update->setText(QApplication::translate("Widget", "\345\210\267\346\226\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
