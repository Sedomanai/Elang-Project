/********************************************************************************
** Form generated from reading UI file 'texture_widget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef TEXTURE_WIDGET_UI_H
#define TEXTURE_WIDGET_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QWidget>
#include "../extension/view.h"

QT_BEGIN_NAMESPACE

class Ui_QElangTextureWidgetUI
{
public:
    QGridLayout *gridLayout;
    el::QElangViewSignaled *view;
    QScrollBar *verti;
    QScrollBar *hori;

    void setupUi(QWidget *QElangTextureWidgetUI)
    {
        if (QElangTextureWidgetUI->objectName().isEmpty())
            QElangTextureWidgetUI->setObjectName("QElangTextureWidgetUI");
        QElangTextureWidgetUI->resize(477, 444);
        gridLayout = new QGridLayout(QElangTextureWidgetUI);
        gridLayout->setSpacing(2);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        view = new el::QElangViewSignaled(QElangTextureWidgetUI);
        view->setObjectName("view");

        gridLayout->addWidget(view, 0, 0, 1, 1);

        verti = new QScrollBar(QElangTextureWidgetUI);
        verti->setObjectName("verti");
        verti->setOrientation(Qt::Vertical);

        gridLayout->addWidget(verti, 0, 1, 2, 1);

        hori = new QScrollBar(QElangTextureWidgetUI);
        hori->setObjectName("hori");
        hori->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(hori, 1, 0, 1, 1);


        retranslateUi(QElangTextureWidgetUI);

        QMetaObject::connectSlotsByName(QElangTextureWidgetUI);
    } // setupUi

    void retranslateUi(QWidget *QElangTextureWidgetUI)
    {
        QElangTextureWidgetUI->setWindowTitle(QCoreApplication::translate("QElangTextureWidgetUI", "Texture Widget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QElangTextureWidgetUI: public Ui_QElangTextureWidgetUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // TEXTURE_WIDGET_UI_H
