#include "OneImageInterface.h"

#include "OneImageView.h"

OneImageInterface::OneImageInterface(QWidget *parent){
	OneImageInterface::parent=parent;
	filePath = "";
}

OneImageInterface::~OneImageInterface(){
	//supprime deja quand le central widget change
	//delete oneImageView;
}

void OneImageInterface::saveCurrentImage(void){
	dynamic_cast<OneImageView*>(parent)->getImage().save(filePath);
}

void OneImageInterface::saveAsCurrentImage(QString newPath){
	dynamic_cast<OneImageView*>(parent)->getImage().save(newPath);
}

QString OneImageInterface::getFilePath(void){
	return filePath;
}

void OneImageInterface::setFilePath(QString path){
	filePath = path;
}