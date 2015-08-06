#include "OneImageView.h"

#include <qapplication.h>
#include <qdesktopwidget.h>
#include <qfiledialog.h>
#include <qdir.h>

OneImageView::OneImageView(QMainWindow *parent):
	QWidget(parent->centralWidget()),
	oneImageInterface(this)
{
	mainWindow = parent;
	imageAff = new QLabel(this);
}
OneImageView::~OneImageView(){

}
void OneImageView::adjustWindow(){
	int screenNb = QApplication::desktop()->screenNumber(mainWindow);
	int width = QApplication::desktop()->screenGeometry(screenNb).width();
	int height = QApplication::desktop()->screenGeometry(screenNb).height();

	int widthLabel = width- 500;
	int heightLabel= height - 120;
	mainWindow->setGeometry(50 + (width*screenNb),50,widthLabel,heightLabel);

	width= widthLabel - 10; 
	height=heightLabel - 10;

	imageAff->resize(width,height);

	
	if(image.width()>width || image.height()>height){
		imageAff->setPixmap(imageToQPixmap(image).scaled(imageAff->width(),imageAff->height(),Qt::KeepAspectRatio));
		
		int x = (width-imageAff->pixmap()->width())/2;

		imageAff->move(x,20);
	}
	else{
		int x = (width-image.width())/2;

		imageAff->move(x,20);
		imageAff->setPixmap(imageToQPixmap(image));
	}
	
}

void OneImageView::newImage(QString filePath){

	image = QImage(filePath);
	adjustWindow();
}

void OneImageView::newImage(QImage img){
	image = QImage(img);
	adjustWindow();
}

void OneImageView::saveCurrentImage(){
	oneImageInterface.saveCurrentImage();
}
void OneImageView::saveAsCurrentImage(QString newPath){
	oneImageInterface.saveAsCurrentImage(newPath);
}

QPixmap OneImageView::imageToQPixmap(QImage img){
	QPixmap p = QPixmap();

	p.convertFromImage(img);
	
	return p;
}

QImage OneImageView::getImage(){
	return image;
}

bool OneImageView::openFile(QWidget *parent){
	oneImageInterface.setFilePath(QString(QFileDialog::getOpenFileName(parent,"Ouvrir un fichier","/home","Images (*.jpg; *.png)")));
	
	if(oneImageInterface.getFilePath() !=""){
		newImage(oneImageInterface.getFilePath());
		return true;
	}

	return false;
}

QString OneImageView::getFilePath(void){
	return oneImageInterface.getFilePath();

}