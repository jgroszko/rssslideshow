#include <QTime>
#include <QDebug>
#include <QList>
#include <QTimer>
#include <QThread>

#include <kglobal.h>
#include <kconfig.h>
#include <kconfiggroup.h>

#include "FeedReadWorker.h"
#include "RssSlideShowSaver.h"

RssSlideShowSaver::RssSlideShowSaver(WId wid) : KScreenSaver(wid)
{
	readConfig();

	m_Scene = new QGraphicsScene();
	m_PixmapItem = new QGraphicsPixmapItem();
	m_Scene->addItem(m_PixmapItem);

	m_View = new QGraphicsView(m_Scene);
	m_View->setStyleSheet("QGraphicsView { border-style: none; }");
	m_View->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
	m_View->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_View->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_Scene->setSceneRect(0, 0, width(), height());

	embed(m_View);

	m_View->show();

	QTimer* feedTimer = new QTimer(this);
	connect(feedTimer, SIGNAL(timeout()), this, SLOT(updateFeeds()));
	feedTimer->start(1000 * 60 * 60); // 1 hour

	updateFeeds();

	m_Timeline = new QTimeLine(m_Delay, this);
	m_Timeline->setFrameRange(0, m_Delay);
	connect(m_Timeline, SIGNAL(frameChanged(int)), this, SLOT(updateEffect(int)));
	connect(m_Timeline, SIGNAL(finished()), this, SLOT(nextImage()));
}

void RssSlideShowSaver::readConfig()
{
	KConfigGroup config(KGlobal::config(), "Settings");
	m_Feeds = config.readEntry("Feeds", "").split("|");
	m_Delay = config.readEntry("Delay", 10) * 1000;
	m_RandomPosition = config.readEntry("RandomPosition", true);
}

void RssSlideShowSaver::updateFeeds()
{
	QList<QUrl> feeds;
	for(int i = 0; i < m_Feeds.count(); i++)
	{
		feeds.append(QUrl(m_Feeds.at(i)));
	}

	FeedReadWorker* worker = new FeedReadWorker(feeds);
	QThread* workerThread = new QThread(this);

	connect(workerThread, SIGNAL(started()), worker, SLOT(doWork()));
        connect(workerThread, SIGNAL(finished()), worker, SLOT(deleteLater()));
	connect(worker, SIGNAL(newImage(KUrl)), this, SLOT(newImage(KUrl)));
	worker->moveToThread(workerThread);

        workerThread->start();
}

void RssSlideShowSaver::newImage(KUrl url)
{
	m_Images.append(url.toLocalFile());

	if(m_PixmapItem->pixmap().isNull())
		nextImage();
}

void RssSlideShowSaver::nextImage()
{
	if(m_ImageQueue.isEmpty())
	{
		if(m_Images.isEmpty())
		{
			qDebug() << "No images :(";
			return;
		}

		QList<QString> imagesStaging;
		for(int i = 0; i < m_Images.count(); i++)
			imagesStaging.append(m_Images.at(i));

		qsrand(QTime::currentTime().msec());
		while(!imagesStaging.isEmpty())
		{			
			m_ImageQueue.enqueue(
				imagesStaging.takeAt(
					qrand() % imagesStaging.count()
					));
		}
	}

	QString currentImage = m_ImageQueue.dequeue();
	qDebug() << "Current image now: " << currentImage;
	qDebug() << "Images on queue: " << m_ImageQueue.count();

	m_PixmapItem->setPixmap(QPixmap(currentImage));

	int width = m_PixmapItem->pixmap().width();
	int height = m_PixmapItem->pixmap().height();

	int sceneWidth = m_View->width();
	int sceneHeight = m_View->height();

	int availableTopRange = (sceneHeight - height);
	int availableLeftRange = (sceneWidth - width);

	int newTop = 0;
	int newLeft = 0;

	if(m_RandomPosition && availableTopRange > 0)
	{
		newTop = qrand() % availableTopRange;
	}
	else
	{
		newTop = (availableTopRange / 2);
	}
	
	if(m_RandomPosition && availableLeftRange > 0)
	{
		newLeft = qrand() % availableLeftRange;
	}
	else
	{
		newLeft = (availableLeftRange / 2);
	}
	
	m_ImageTop = newTop;
	m_ImageLeft = newLeft;

	m_PixmapItem->setPos(m_ImageLeft, m_ImageTop);

	m_Timeline->start();
}

void RssSlideShowSaver::updateEffect(int frame)
{
	const double fadePeriod = 200;
	const double frameRange = m_Delay;

	double effectProgress = 0.0;
	bool ending = false;

	if(frame < fadePeriod)
		effectProgress = (double)frame / fadePeriod;
	else if(frame > fadePeriod && (frame < (frameRange - fadePeriod)))
		effectProgress = 1.0;
	else if(frame > (frameRange - fadePeriod))
	{
		ending = true;
		effectProgress = 1 - (((double)frame - (frameRange - fadePeriod)) / fadePeriod);
	}

	m_PixmapItem->setOpacity(effectProgress);

	double motionRange = (double)m_PixmapItem->pixmap().width() * 0.05;
	double t = 1 - effectProgress;
	double easedProgress = 1 - t*t*t*t;

	m_PixmapItem->setPos(
		(ending
		 ? (m_ImageLeft + ((1.0 - easedProgress))*motionRange)
		 : (m_ImageLeft-motionRange) + (easedProgress*motionRange)),
		m_ImageTop
		);
}
