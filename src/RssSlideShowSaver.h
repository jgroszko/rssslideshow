#ifndef RSSSLIDESHOWSAVER_H
#define RSSSLIDESHOWSAVER_H

#include <QQueue>
#include <QList>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimeLine>

#include <kurl.h>
#include <kscreensaver.h>

#include "ImageDatabase.h"

class RssSlideShowSaver : public KScreenSaver
{
	Q_OBJECT
public:
	RssSlideShowSaver(WId wid);

	void readConfig();
	void update();

protected slots:
	void updateFeeds();

	void newImage(KUrl url);

	void nextImage();
	void updateEffect(int frame);
protected:
	/* Config Options */
	QList<QString> m_Feeds;
	int m_Delay;
	bool m_RandomPosition;
	bool m_Transition;
	int m_TransitionDuration;

	QGraphicsView* m_View;
	QGraphicsScene* m_Scene;
	QGraphicsPixmapItem* m_PixmapItem;
	QTimeLine* m_Timeline;

	int m_ImageLeft, m_ImageTop;
	int m_FrameRange;

	QList<QString> m_Images;
	ImageDatabase m_ImagesDb;
        QQueue<QString> m_ImageQueue;
};

#endif
