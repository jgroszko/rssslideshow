#ifndef RSSSLIDESHOWINTERFACE_H
#define RSSSLIDESHOWINTERFACE_H

#include <kscreensaver.h>

class RssSlideShowInterface : public KScreenSaverInterface
{
public:
	virtual KAboutData* aboutData();

	virtual KScreenSaver* create(WId id);

	virtual QDialog* setup();
};

#endif
