/********************************************************************************
** Form generated from reading UI file 'auto_gen.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef AUTO_GEN_UI_H
#define AUTO_GEN_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AtlasAutoGeneratorUI
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QRadioButton *ltrButton;
    QRadioButton *ttbButton;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpinBox *marginBox;
    QPushButton *generateButton;
    QButtonGroup *buttonGroup;

    void setupUi(QDialog *ElangAtlasAutoGeneratorUI)
    {
        if (ElangAtlasAutoGeneratorUI->objectName().isEmpty())
            ElangAtlasAutoGeneratorUI->setObjectName("ElangAtlasAutoGeneratorUI");
        ElangAtlasAutoGeneratorUI->resize(223, 101);
        verticalLayout_2 = new QVBoxLayout(ElangAtlasAutoGeneratorUI);
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(9, 9, 9, 9);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        ltrButton = new QRadioButton(ElangAtlasAutoGeneratorUI);
        buttonGroup = new QButtonGroup(ElangAtlasAutoGeneratorUI);
        buttonGroup->setObjectName("buttonGroup");
        buttonGroup->addButton(ltrButton);
        ltrButton->setObjectName("ltrButton");
        ltrButton->setChecked(true);

        horizontalLayout->addWidget(ltrButton);

        ttbButton = new QRadioButton(ElangAtlasAutoGeneratorUI);
        buttonGroup->addButton(ttbButton);
        ttbButton->setObjectName("ttbButton");

        horizontalLayout->addWidget(ttbButton);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(ElangAtlasAutoGeneratorUI);
        label->setObjectName("label");

        horizontalLayout_2->addWidget(label);

        marginBox = new QSpinBox(ElangAtlasAutoGeneratorUI);
        marginBox->setObjectName("marginBox");
        marginBox->setMinimum(0);
        marginBox->setMaximum(2048);
        marginBox->setValue(50);

        horizontalLayout_2->addWidget(marginBox);


        verticalLayout->addLayout(horizontalLayout_2);

        generateButton = new QPushButton(ElangAtlasAutoGeneratorUI);
        generateButton->setObjectName("generateButton");

        verticalLayout->addWidget(generateButton);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(ElangAtlasAutoGeneratorUI);

        QMetaObject::connectSlotsByName(ElangAtlasAutoGeneratorUI);
    } // setupUi

    void retranslateUi(QDialog *ElangAtlasAutoGeneratorUI)
    {
        ElangAtlasAutoGeneratorUI->setWindowTitle(QCoreApplication::translate("AtlasAutoGeneratorUI", "Atlas Auto Generate", nullptr));
        ltrButton->setText(QCoreApplication::translate("AtlasAutoGeneratorUI", "Left to Right", nullptr));
        ttbButton->setText(QCoreApplication::translate("AtlasAutoGeneratorUI", "Top to Bottom", nullptr));
        label->setText(QCoreApplication::translate("AtlasAutoGeneratorUI", "Margin", nullptr));
        generateButton->setText(QCoreApplication::translate("AtlasAutoGeneratorUI", "Generate", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AtlasAutoGeneratorUI: public Ui_AtlasAutoGeneratorUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // AUTO_GEN_UI_H
