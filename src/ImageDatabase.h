#ifndef IMAGEDATABASE_H
#define IMAGEDATABASE_H

#include <QtSql>
#include <QString>

class ImageDatabase : public QObject
{
	Q_OBJECT
public:
	ImageDatabase();

	void open();
	void close();

	bool exists(QString url);
	void add(QString url);
	
	QStringList get(int limit = 50);

protected:
	QSqlDatabase m_db;
};

#endif
