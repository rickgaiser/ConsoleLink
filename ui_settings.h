/********************************************************************************
** Form generated from reading UI file 'settings.ui'
**
** Created: Wed May 5 00:43:04 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogSettings
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *ip;
    QCheckBox *cbClearOnReset;
    QCheckBox *cbClearOnShutdown;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *ok;
    QPushButton *cancel;

    void setupUi(QDialog *DialogSettings)
    {
        if (DialogSettings->objectName().isEmpty())
            DialogSettings->setObjectName(QString::fromUtf8("DialogSettings"));
        DialogSettings->resize(271, 161);
        verticalLayout = new QVBoxLayout(DialogSettings);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        label_2 = new QLabel(DialogSettings);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);

        horizontalLayout_3->addWidget(label_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(DialogSettings);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        ip = new QLineEdit(DialogSettings);
        ip->setObjectName(QString::fromUtf8("ip"));
        ip->setMaxLength(15);
        ip->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(ip);


        verticalLayout->addLayout(horizontalLayout_2);

        cbClearOnReset = new QCheckBox(DialogSettings);
        cbClearOnReset->setObjectName(QString::fromUtf8("cbClearOnReset"));

        verticalLayout->addWidget(cbClearOnReset);

        cbClearOnShutdown = new QCheckBox(DialogSettings);
        cbClearOnShutdown->setObjectName(QString::fromUtf8("cbClearOnShutdown"));

        verticalLayout->addWidget(cbClearOnShutdown);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        ok = new QPushButton(DialogSettings);
        ok->setObjectName(QString::fromUtf8("ok"));

        horizontalLayout->addWidget(ok);

        cancel = new QPushButton(DialogSettings);
        cancel->setObjectName(QString::fromUtf8("cancel"));

        horizontalLayout->addWidget(cancel);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(DialogSettings);
        QObject::connect(cancel, SIGNAL(clicked()), DialogSettings, SLOT(reject()));
        QObject::connect(ok, SIGNAL(clicked()), DialogSettings, SLOT(accept()));

        QMetaObject::connectSlotsByName(DialogSettings);
    } // setupUi

    void retranslateUi(QDialog *DialogSettings)
    {
        DialogSettings->setWindowTitle(QApplication::translate("DialogSettings", "Settings", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("DialogSettings", "Settings", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DialogSettings", "IP Adress:", 0, QApplication::UnicodeUTF8));
        ip->setInputMask(QApplication::translate("DialogSettings", "000.000.000.000;_", 0, QApplication::UnicodeUTF8));
        cbClearOnReset->setText(QApplication::translate("DialogSettings", "Clear log on reset", 0, QApplication::UnicodeUTF8));
        cbClearOnShutdown->setText(QApplication::translate("DialogSettings", "Clear log on shutdown", 0, QApplication::UnicodeUTF8));
        ok->setText(QApplication::translate("DialogSettings", "OK", 0, QApplication::UnicodeUTF8));
        cancel->setText(QApplication::translate("DialogSettings", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DialogSettings: public Ui_DialogSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_H
