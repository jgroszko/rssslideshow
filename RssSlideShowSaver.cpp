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
	m_View->setStyleSheet("QGraphicsView { background: black; border-style: none; }");
	m_View->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_View->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	embed(m_View);

	m_View->show();

	QTimer* feedTimer = new QTimer(this);
	connect(feedTimer, SIGNAL(timeout()), this, SLOT(updateFeeds()));
	feedTimer->start(1000 * 60 * 60); // 1 hour

	updateFeeds();

	QTimer* imageTimer = new QTimer(this);
	connect(imageTimer, SIGNAL(timeout()), this, SLOT(nextImage()));
	imageTimer->start(m_Delay);
}

void RssSlideShowSaver::readConfig()
{
	KConfigGroup config(KGlobal::config(), "Settings");
	m_Feeds = config.readEntry("Feeds", "").split("|");
	m_Delay = config.readEntry("Delay", 10) * 1000;
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
}
