#include <kdebug.h>

#include "RssSlideShowInterface.h"
#include "RssSlideShowSetup.h"

KAboutData* RssSlideShowInterface::aboutData()
{
	KAboutData* aboutData = new KAboutData("rssslideshow.kss",
					      0,
					       ki18n("RSS Slide Show"),
					      "3.0.0",
					      ki18n("A slideshow of pictures pulled from an RSS feed."),
					      KAboutData::License_GPL);

	aboutData->addAuthor(ki18n("John Groszko"), KLocalizedString(), "john@tinythunk.com", "http://tinythunk.com");

	return aboutData;
}

KScreenSaver* RssSlideShowInterface::create(WId wid)
{
	return new RssSlideShowSaver(wid);
}

QDialog* RssSlideShowInterface::setup()
{
	return new RssSlideShowSetup();
}
