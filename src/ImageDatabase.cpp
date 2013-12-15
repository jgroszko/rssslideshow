#include "ImageDatabase.h"

ImageDatabase::ImageDatabase()
{
	m_db = QSqlDatabase::addDatabase("QSQLITE");

	m_db.setDatabaseName("rssslideshow.db");
}

void ImageDatabase::open()
{
	m_db.open();

	if(!m_db.tables().contains("images"))
	{
		QSqlQuery query;
		query.exec("CREATE TABLE images "
			   "(id INTEGER PRIMARY KEY AUTOINCREMENT, "
			   " timestamp DATETIME DEFAULT CURRENT_TIMESTAMP, "
			   " url CHAR(255));");
	}
}

void ImageDatabase::close()
{
	m_db.close();
}

void ImageDatabase::addImage(QString url)
{
	QSqlQuery query;
	query.prepare("INSERT INTO images (URL)"
		      "VALUES (:url);");
	query.bindValue("url", url);
	query.exec();
}

QStringList ImageDatabase::getImages(int limit)
{
	QSqlQuery query("SELECT url FROM images ORDER BY RANDOM() LIMIT :limit");
	query.bindValue("limit", limit);
	query.exec();
	
	QStringList result;
	while(query.next())
		result.append(query.value(0).toString());

	return result;
}
