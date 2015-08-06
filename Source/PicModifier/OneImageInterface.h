#ifndef ONEIMAGEINTERFACE_H
#define ONEIMAGEINTERFACE_H

#include <qmainwindow.h>

class OneImageInterface{

	public: 
		OneImageInterface(QWidget *parent);
		~OneImageInterface();
		
		//sauvegarder une image à sa position d'origine
		void saveCurrentImage(void);
		//sauvegarder une image avec un nom et un emplacement choisit par l'usager
		void saveAsCurrentImage(QString newPath);

		QString getFilePath(void);
		void setFilePath(QString path);
		
private:
		//chemin d'accès du fichier
		QString filePath;
		//lien vers le centralWidget
		QWidget *parent;
};

#endif