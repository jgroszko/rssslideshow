#ifndef FEEDREADTHREAD_H
#define FEEDREADTHREAD_H

#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <kurl.h>

class FeedReadWorker : public QObject
{
	Q_OBJECT
public:	
	FeedReadWorker(QList<QUrl> feeds);

public slots:
	void doWork();

signals:
	void newImage(KUrl url);
	void finished();

protected:
	void requestImage(QString feedName, KUrl url);

	KUrl localPath(QString feedName, KUrl url);

	QList<QUrl> m_Feeds;

	QNetworkAccessManager* m_QNAM;
};

#endif
