/********************************************************************************
** Form generated from reading UI file 'maindlg.ui'
**
** Created: Wed May 6 13:15:05 2015
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINDLG_H
#define UI_MAINDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>
#include <QtWebKit/QWebView>

QT_BEGIN_NAMESPACE

class Ui_maindlg
{
public:
    QWebView *webView;

    void setupUi(QWidget *maindlg)
    {
        if (maindlg->objectName().isEmpty())
            maindlg->setObjectName(QString::fromUtf8("maindlg"));
        maindlg->setWindowModality(Qt::NonModal);
        maindlg->resize(843, 560);
        webView = new QWebView(maindlg);
        webView->setObjectName(QString::fromUtf8("webView"));
        webView->setGeometry(QRect(310, 140, 351, 301));
        webView->setUrl(QUrl(QString::fromUtf8("about:blank")));

        retranslateUi(maindlg);

        QMetaObject::connectSlotsByName(maindlg);
    } // setupUi

    void retranslateUi(QWidget *maindlg)
    {
        maindlg->setWindowTitle(QApplication::translate("maindlg", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class maindlg: public Ui_maindlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINDLG_H
