#include "MassImageInterface.h"

#include "MassImageView.h"
#include "Tools.h"
#include "SegmentationMono.h"
#include "SegmentationCouleur.h"
#include "FiltreLineaire.h"
#include "FiltreNonLineaire.h"
#include "Convolution.h"

#include <qdir.h>
#include <qpixmap.h>

MassImageInterface::MassImageInterface(QWidget *parent)
{
	MassImageInterface::parent = parent;
	folderPath = "";
}
MassImageInterface::~MassImageInterface(){
	//supprime deja quand le central widget change
	//delete massImageView;
}


void MassImageInterface::addFilterToList(Modifier *filtre){
	listFiltreToApply.append(filtre);
}

void MassImageInterface::removeFilterFromList(int pos){
	delete listFiltreToApply.takeAt(pos);
}

QString MassImageInterface::getFolderPath(void){
	return folderPath;
}

void MassImageInterface::setFolderPath(QString path){
	folderPath = path;
}

bool MassImageInterface::addImages(QStringList fileList){
	bool folderWithImage = false;
	QDir dirTemp = QDir(folderPath);

	if(fileList.size() >0){
		for(int i =0;i<fileList.size();i++){
			listImage[fileList[i]] =  QImage(dirTemp.absolutePath() + '/' + fileList[i]);
		}
		folderWithImage = true;
	}

	return folderWithImage;
}

QList<Modifier*> MassImageInterface::getFilterList(void){
	return listFiltreToApply;
}

QPixmap MassImageInterface::applyFilter(QPixmap imageApercu){
	QString type = "";
	QImage tempImg;

	Q_FOREACH(Modifier *m, getFilterList()){
		type= typeid(*m).name();

		if(type =="class FiltreLineaire"){
			tempImg = FiltreLineaire::execute(imageApercu.toImage(),(dynamic_cast<FiltreLineaire*>(m))->listFactor);
		}
		else if(type =="class FiltreNonLineaire"){
			tempImg = FiltreNonLineaire::execute(imageApercu.toImage(),(dynamic_cast<FiltreNonLineaire*>(m))->listFactor);
		}
		else if(type =="class Crop"){
			tempImg = Crop::execute(imageApercu.toImage(),(dynamic_cast<Crop*>(m))->startX,(dynamic_cast<Crop*>(m))->startY,(dynamic_cast<Crop*>(m))->endX,(dynamic_cast<Crop*>(m))->endY);
		}
		else if(type =="class SegmentationCouleur"){
			tempImg = SegmentationCouleur::execute(imageApercu.toImage(),(dynamic_cast<SegmentationCouleur*>(m))->seuil);
		}
		else if(type =="class SegmentationMono"){
			tempImg = SegmentationMono::execute(imageApercu.toImage(),(dynamic_cast<SegmentationMono*>(m))->seuil);
		}
		else if(type =="class Rotation"){
			tempImg = Rotation::execute(imageApercu.toImage(),(dynamic_cast<Rotation*>(m))->nbRotation);
		}
		else if(type =="class Miroir"){
			tempImg = Miroir::execute(imageApercu.toImage(),(dynamic_cast<Miroir*>(m))->direction);
		}
		else if(type =="class ResizeScale"){
			tempImg = ResizeScale::execute(imageApercu.toImage(),(dynamic_cast<ResizeScale*>(m))->xRatio,(dynamic_cast<ResizeScale*>(m))->yRatio);
		}
		else if(type =="class Convolution"){
			tempImg = Convolution::execute(imageApercu.toImage(),(dynamic_cast<Convolution*>(m))->facteur,(dynamic_cast<Convolution*>(m))->type);
		}

		imageApercu = imageApercu.fromImage(tempImg);
		
	}

	return imageApercu;
}

void MassImageInterface::saveImage(QImage img, QString filePath){
	bool test = img.save(filePath);
}

void MassImageInterface::saveAll(QString filePath,int saveConfig,QString newFileName){
	QMapIterator<QString,QImage> image(listImage);
	
	int numImg = 0;
	int total = listImage.count();

	while(image.hasNext()){	
		image.next();

		QPixmap pix = QPixmap();
		pix = pix.fromImage(image.value());
		QImage iOutput = applyFilter(pix).toImage();
		
		if(saveConfig == 1){
			saveImage(iOutput, filePath + '/' + image.key());
			
		}
		else if(saveConfig == 2){
			QStringList filename = image.key().split('.');
			QString name = QString(filename[0] + "(1)." + filename[1]);

			saveImage(iOutput,filePath + '/' + name);
		}
		else if(saveConfig == 3){
			if(newFileName == ""){
				newFileName = "Sans titre";
			}

			QStringList filename = image.key().split('.');
			QString name = QString(newFileName + "(" + QString::number(numImg) + ")." + filename[1]);

			saveImage(iOutput,filePath + '/' + name);
		}
		(dynamic_cast<MassImageView*>(parent))->changeProgressValue(numImg,total);

		numImg++;
	}
	(dynamic_cast<MassImageView*>(parent))->changeProgressValue(99,100);
}