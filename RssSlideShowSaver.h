#ifndef RSSSLIDESHOWSAVER_H
#define RSSSLIDESHOWSAVER_H

#include <QQueue>
#include <QList>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include <kurl.h>
#include <kscreensaver.h>

class RssSlideShowSaver : public KScreenSaver
{
	Q_OBJECT
public:
	RssSlideShowSaver(WId wid);

protected slots:
	void updateFeeds();

	void newImage(KUrl url);

	void nextImage();
protected:
	/* Config Options */
	QList<QString> m_Feeds;
	int m_Delay;
	bool m_RandomPosition;

	QGraphicsView* m_View;
	QGraphicsScene* m_Scene;
	QGraphicsPixmapItem* m_PixmapItem;

	void readConfig();

	QList<QString> m_Images;
        QQueue<QString> m_ImageQueue;
};

#endif
