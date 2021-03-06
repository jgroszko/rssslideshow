#include <QDebug>

#include <kglobal.h>
#include <kstandarddirs.h>
#include <kcomponentdata.h>

#include "ImageDatabase.h"

ImageDatabase::ImageDatabase()
{
	m_db = QSqlDatabase::addDatabase("QSQLITE");

	QString fullDirectory =
	  KStandardDirs::locateLocal("cache",
				     "rssslideshow",
				     KGlobal::activeComponent());
		
	if(!QDir(fullDirectory).exists())
	  QDir(fullDirectory).mkpath(fullDirectory);		     

	m_db.setDatabaseName(fullDirectory + QDir::separator() + "rssslideshow.db");
}

void ImageDatabase::open()
{
	if(!m_db.open())
	{
		qDebug() << "Unable to open database " << m_db.lastError();
	}

	if(!m_db.tables().contains("images"))
	{
		QSqlQuery query;
		query.prepare("CREATE TABLE images "
			      "(id INTEGER PRIMARY KEY AUTOINCREMENT, "
			      " timestamp DATETIME DEFAULT CURRENT_TIMESTAMP, "
			      " url CHAR(255) UNIQUE)");
		if(!query.exec())
		{
			qDebug() << "Unable to create table images " << query.lastError();
		}
	}
}

void ImageDatabase::close()
{
	m_db.close();
}

bool ImageDatabase::exists(QString url)
{
	QSqlQuery query;
	query.prepare("SELECT COUNT() FROM images "
		      "WHERE url=:url");
	query.bindValue("url", url);
	if(!query.exec())
		qDebug() << "Failed to query for image " << url << " " << query.lastError();

	query.first();

	return query.value(0).toInt() > 0;
}

void ImageDatabase::add(QString url)
{
	if(!exists(url))
	{
		QSqlQuery query;
		query.prepare("INSERT INTO images (URL)"
			      "VALUES (:url)");
		query.bindValue("url", url);
		if(!query.exec())
		{
			qDebug() << "Failed to add image " << url << " " << query.lastError();
		}
		else
		{
			qDebug() << "Added " << url;
		}
	}
	else
	{
		qDebug() << "Already got image " << url;
	}
}	

QStringList ImageDatabase::get(int limit)
{
	QSqlQuery query("SELECT url FROM images ORDER BY RANDOM() LIMIT :limit");
	query.bindValue("limit", limit);
	query.exec();
	
	QStringList result;
	while(query.next())
		result.append(query.value(0).toString());

	return result;
}
