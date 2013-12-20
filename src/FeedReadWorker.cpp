#include "FeedReadWorker.h"

#include <QEventLoop>
#include <QStringList>
#include <QXmlQuery>
#include <QThread>
#include <QRegExp>
#include <QNetworkRequest>
#include <QFile>
#include <QDir>

#include <kglobal.h>
#include <kurl.h>
#include <kstandarddirs.h>
#include <kcomponentdata.h>

FeedReadWorker::FeedReadWorker(QList<QUrl> feeds)
	: m_Feeds ( feeds )
{
	m_QNAM = new QNetworkAccessManager(this);
}

KUrl FeedReadWorker::localPath(QString feedName, KUrl imageUrl)
{
	QString fileName = imageUrl.fileName();

	QString fullDirectory =
		KStandardDirs::locateLocal(
			"cache",
			QString("rssslideshow") + QDir::separator() + feedName,
			KGlobal::activeComponent());

	if(!QDir(fullDirectory).exists())
		QDir(fullDirectory).mkpath(fullDirectory);	

	return fullDirectory +
	  QDir::separator() +
	  fileName;
}

void FeedReadWorker::doWork()
{
	while(!m_Feeds.isEmpty())
	{
		QUrl rss = m_Feeds.takeFirst();
		QString feedName = rss.toString()
			.replace(":", "").replace("/", "_");

		QXmlQuery query;
		query.bindVariable("path", QVariant(rss));
		QString q = QString("declare variable $path external;") +
			QString("doc($path)/*:rss//item/description/string()");
		query.setQuery(q);
			
		QStringList items;
		QRegExp imgSrc("src=\"([^\\s\"]+\\.(png|jpg|jpeg|gif))\"");
		if(query.evaluateTo(&items))
		{
			for(int i = 0; i < items.count(); i++)
			{
				imgSrc.indexIn(items.at(i));
				if(imgSrc.captureCount() > 0 &&
				   !imgSrc.cap(1).isEmpty())
				{
					requestImage(feedName, KUrl(imgSrc.cap(1)));
				}
			}
		}
	}

	QThread::currentThread()->quit();
}

void FeedReadWorker::requestImage(QString feedName, KUrl url)
{
	KUrl localImage = localPath(feedName, url);
	if(!QFile(localImage.toLocalFile()).exists())
	{
		QNetworkReply* reply = m_QNAM->get(QNetworkRequest(url));

		// TODO: Do this synchronously
		QEventLoop loop;
		connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
		loop.exec();
	
		if(reply->error() == QNetworkReply::NoError)
		{
			QFile img(localImage.toLocalFile());
			if(img.open(QIODevice::WriteOnly))
			{
				while(!reply->atEnd())
				{
					reply->waitForReadyRead(1000);
					img.write(reply->read(1024));
				}
				reply->close();
				
				img.close();
				
				emit newImage(localImage);
			}		
		}

		reply->deleteLater();
	}
	else
	{
		emit newImage(localImage);
	}
}
