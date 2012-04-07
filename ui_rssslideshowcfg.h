#include <kdialog.h>
#include <klocale.h>

/********************************************************************************
** Form generated from reading UI file 'rssslideshowcfg.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RSSSLIDESHOWCFG_H
#define UI_RSSSLIDESHOWCFG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "klineedit.h"
#include "knuminput.h"
#include "kpushbutton.h"

QT_BEGIN_NAMESPACE

class Ui_SlideShowCfg
{
public:
    QGridLayout *gridLayout;
    QCheckBox *mCbxZoom;
    QCheckBox *mCbxRandom;
    QCheckBox *mCbxShowName;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *cbSpacer1;
    QCheckBox *mCbxShowPath;
    QCheckBox *mCbxRandomPosition;
    QHBoxLayout *horizontalLayout;
    QLabel *textLabel1_2;
    KIntSpinBox *mDelay;
    QSpacerItem *spacer11;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *lineEdit_FeedToAdd;
    QListWidget *listWidget_Feeds;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_AddFeed;
    QPushButton *pushButton_RemoveFeed;
    QSpacerItem *verticalSpacer;
    QFrame *mPreview;

    void setupUi(QWidget *SlideShowCfg)
    {
        if (SlideShowCfg->objectName().isEmpty())
            SlideShowCfg->setObjectName(QString::fromUtf8("SlideShowCfg"));
        SlideShowCfg->resize(456, 429);
        gridLayout = new QGridLayout(SlideShowCfg);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        mCbxZoom = new QCheckBox(SlideShowCfg);
        mCbxZoom->setObjectName(QString::fromUtf8("mCbxZoom"));

        gridLayout->addWidget(mCbxZoom, 0, 0, 1, 2);

        mCbxRandom = new QCheckBox(SlideShowCfg);
        mCbxRandom->setObjectName(QString::fromUtf8("mCbxRandom"));

        gridLayout->addWidget(mCbxRandom, 1, 0, 1, 2);

        mCbxShowName = new QCheckBox(SlideShowCfg);
        mCbxShowName->setObjectName(QString::fromUtf8("mCbxShowName"));

        gridLayout->addWidget(mCbxShowName, 2, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        cbSpacer1 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(cbSpacer1);

        mCbxShowPath = new QCheckBox(SlideShowCfg);
        mCbxShowPath->setObjectName(QString::fromUtf8("mCbxShowPath"));

        horizontalLayout_3->addWidget(mCbxShowPath);


        gridLayout->addLayout(horizontalLayout_3, 3, 0, 1, 2);

        mCbxRandomPosition = new QCheckBox(SlideShowCfg);
        mCbxRandomPosition->setObjectName(QString::fromUtf8("mCbxRandomPosition"));

        gridLayout->addWidget(mCbxRandomPosition, 4, 0, 1, 2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        textLabel1_2 = new QLabel(SlideShowCfg);
        textLabel1_2->setObjectName(QString::fromUtf8("textLabel1_2"));
        textLabel1_2->setWordWrap(false);

        horizontalLayout->addWidget(textLabel1_2);

        mDelay = new KIntSpinBox(SlideShowCfg);
        mDelay->setObjectName(QString::fromUtf8("mDelay"));
        mDelay->setMinimum(1);
        mDelay->setMaximum(240);

        horizontalLayout->addWidget(mDelay);


        gridLayout->addLayout(horizontalLayout, 5, 0, 1, 1);

        spacer11 = new QSpacerItem(20, 19, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(spacer11, 6, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        lineEdit_FeedToAdd = new QLineEdit(SlideShowCfg);
        lineEdit_FeedToAdd->setObjectName(QString::fromUtf8("lineEdit_FeedToAdd"));

        verticalLayout_2->addWidget(lineEdit_FeedToAdd);

        listWidget_Feeds = new QListWidget(SlideShowCfg);
        listWidget_Feeds->setObjectName(QString::fromUtf8("listWidget_Feeds"));
        listWidget_Feeds->setEditTriggers(QAbstractItemView::AllEditTriggers);

        verticalLayout_2->addWidget(listWidget_Feeds);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushButton_AddFeed = new QPushButton(SlideShowCfg);
        pushButton_AddFeed->setObjectName(QString::fromUtf8("pushButton_AddFeed"));

        verticalLayout->addWidget(pushButton_AddFeed);

        pushButton_RemoveFeed = new QPushButton(SlideShowCfg);
        pushButton_RemoveFeed->setObjectName(QString::fromUtf8("pushButton_RemoveFeed"));

        verticalLayout->addWidget(pushButton_RemoveFeed);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_2->addLayout(verticalLayout);


        gridLayout->addLayout(horizontalLayout_2, 7, 0, 1, 4);

        mPreview = new QFrame(SlideShowCfg);
        mPreview->setObjectName(QString::fromUtf8("mPreview"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mPreview->sizePolicy().hasHeightForWidth());
        mPreview->setSizePolicy(sizePolicy);
        mPreview->setFrameShape(QFrame::NoFrame);
        mPreview->setFrameShadow(QFrame::Plain);

        gridLayout->addWidget(mPreview, 0, 2, 7, 2);

        mCbxZoom->raise();
        mCbxRandom->raise();
        mCbxShowName->raise();
        mCbxRandomPosition->raise();
        mPreview->raise();
#ifndef UI_QT_NO_SHORTCUT
        textLabel1_2->setBuddy(mDelay);
#endif // QT_NO_SHORTCUT

        retranslateUi(SlideShowCfg);
        QObject::connect(mCbxZoom, SIGNAL(toggled(bool)), mCbxRandomPosition, SLOT(setDisabled(bool)));
        QObject::connect(mCbxShowName, SIGNAL(toggled(bool)), mCbxShowPath, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(SlideShowCfg);
    } // setupUi

    void retranslateUi(QWidget *SlideShowCfg)
    {
        mCbxZoom->setText(tr2i18n("Resi&ze images", 0));
        mCbxRandom->setText(tr2i18n("&Random order", 0));
        mCbxShowName->setText(tr2i18n("Show &names", 0));
        mCbxShowPath->setText(tr2i18n("Show &full path", 0));
        mCbxRandomPosition->setText(tr2i18n("Random &position", 0));
        textLabel1_2->setText(tr2i18n("&Delay:", 0));
        mDelay->setSpecialValueText(QString());
        pushButton_AddFeed->setText(tr2i18n("Add", 0));
        pushButton_RemoveFeed->setText(tr2i18n("Remove", 0));
        Q_UNUSED(SlideShowCfg);
    } // retranslateUi

};

namespace Ui {
    class SlideShowCfg: public Ui_SlideShowCfg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // RSSSLIDESHOWCFG_H

