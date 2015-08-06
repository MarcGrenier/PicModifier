#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <qfile.h>
#include <qtextstream.h>

class FileManager{
	public:
		static QList<QString> readFile(QString filePath);
		static void writeFile(QString filePath, QString text);
		static QMap<QString,QVector<float>> textToInfo(QList<QString> listText,int nbElement);
		static QList<QString> orderList(QList<QString> listText,int nbElement);
};

#endif;