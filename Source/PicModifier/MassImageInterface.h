#ifndef MASSIMAGEINTERFACE_H
#define MASSIMAGEINTERFACE_H

#include "Modifier.h"
#include <qmap.h>
#include <qstringlist.h>

class MassImageInterface{

	public:
		MassImageInterface(QWidget *parent);
		~MassImageInterface();
		
		void addFilterToList(Modifier *filtre);
		void removeFilterFromList(int pos);
		
		QString getFolderPath(void);
		void setFolderPath(QString path);

		bool addImages(QStringList fileList);

		QList<Modifier*> getFilterList(void);

		QPixmap applyFilter(QPixmap imageApercu);

		void saveImage(QImage img, QString filePath);
		void saveAll(QString filePath,int saveConfig,QString newFileName);

	private:
		QWidget *parent;
		//liste de toutes les images
		QMap<QString,QImage> listImage;
		//dosier où se trouve toutes les images
		QString folderPath;

		QList<Modifier*> listFiltreToApply;
};

#endif