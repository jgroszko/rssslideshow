#ifndef RSSSLIDESHOWCONFIG_H
#define RSSSLIDESHOWCONFIG_H

#include <QWidget>
#include "ui_rssslideshowcfg.h"

class RssSlideShowConfig : public QWidget, public Ui::SlideShowCfg
{
public:
  RssSlideShowConfig( QWidget *parent ) : QWidget( parent ) {
    setupUi( parent );
  }
};

#endif
