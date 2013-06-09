#ifndef RSSSLIDESHOWSETUP_H
#define RSSSLIDESHOWSETUP_H

#include <KDialog>

#include "RssSlideShowSaver.h"
#include "RssSlideShowConfig.h"

class RssSlideShowSetup : public KDialog
{
  Q_OBJECT
public:
  RssSlideShowSetup(QWidget *parent=NULL);
  ~RssSlideShowSetup();

protected:
  void readSettings();

protected slots:
  void slotOk();
  void writeSettings();
  void toggleTransition();
  void slotAddFeed();
  void slotRemoveFeed();

private:
  RssSlideShowSaver *mSaver;
  RssSlideShowConfig *cfg;
};

#endif
