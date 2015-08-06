#ifndef ONEIMAGEVIEW_H
#define ONEIMAGEVIEW_H

#include <qwidget.h>
#include <qlabel.h>
#include <qimage.h>
#include <qmainwindow.h>

#include "OneImageInterface.h"

class OneImageView: public QWidget{

	public:
		OneImageView(QMainWindow *parent);
		~OneImageView();
		//ajust la fenêtre selon la grandeur de l'écran
		void adjustWindow();
		
		//ajout d'une image à cet interface
		void newImage(QString filePath);
		void newImage(QImage img);

		void saveCurrentImage();
		void saveAsCurrentImage(QString newPath);

		QPixmap imageToQPixmap(QImage img);
		QImage getImage(void);
		QString getFilePath(void);
		//ouvrir une fenêtre de dialogue pour choisir une image
		bool openFile(QWidget* parent);
		
	private:
		QMainWindow *mainWindow;
		OneImageInterface oneImageInterface;
		//image à l'écran
		QImage image;
		//label dans lequel l'image ets contenu
		QLabel* imageAff;
};

#endif