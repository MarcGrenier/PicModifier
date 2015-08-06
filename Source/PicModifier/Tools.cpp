#include "Tools.h"
#include "FileManager.h"
#include <qdir.h>

/***Rotation***/
Rotation::Rotation(int nbRotation){
	Rotation::nbRotation = nbRotation;
}
QImage Rotation::execute(QImage img,int nbRotation){
	for(int i=0; i<nbRotation ;i++){
		img = img.transformed(QTransform().rotate(90));
	}

	return img;
}

/***Mirroir***/
Miroir::Miroir(char direction){
	Miroir::direction = direction;
}
QImage Miroir::execute(QImage img,char direction){
	if(direction =='V'){
		img  = img.mirrored();
	}
	else if (direction == 'H'){
		img  = img.mirrored(true,false);
	}

	return img;
}

/***ResizeScale***/
ResizeScale::ResizeScale(float xRatio, float yRatio){
	ResizeScale::xRatio = xRatio;
	ResizeScale::yRatio = yRatio;
}
QImage ResizeScale::execute(QImage img, float xRatio, float yRatio){

	img = img.transformed(QTransform().scale(xRatio,yRatio));

	return img;
}
QList<Modifier::proprieteGenerique> ResizeScale::feedResizeScaleProperties(){
	QList<Modifier::proprieteGenerique> propriete;

	proprieteGenerique p;
	p.max = 1920;
	p.min = 0.1;
	p.name = "ratio X";
	p.type = "DoubleSpiner";
	propriete.append(p);
	
	p.name = "ratio Y";
	propriete.append(p);

	return propriete;
}
QVector<float> ResizeScale::getDefaultValueResizeScale(void){
	QVector<float> value;
	value <<1.0<<1.0;
	return value;
}

/***ResizePixel***/
ResizePixel::ResizePixel(float xPixel, float yPixel){
	ResizePixel::xPixel = xPixel;
	ResizePixel::yPixel = yPixel;
}
QImage ResizePixel::execute(QImage img, float xPixel, float yPixel){

	img = img.scaled(xPixel,yPixel);

	return img;
}
QList<Modifier::proprieteGenerique> ResizePixel::feedResizePixelProperties(){
	QList<Modifier::proprieteGenerique> propriete;

	proprieteGenerique p;
	p.max = 100000;
	p.min = 1;
	p.name = "dimension X";
	p.type = "Spinner";
	p.toolTip = "px";
	propriete.append(p);
	
	p.name = "dimension Y";
	propriete.append(p);

	return propriete;
}

/***Crop***/
Crop::Crop(int startX, int startY,int endX, int endY){
	Crop::startX = startX;
	Crop::startY = startY;
	Crop::endX = endX; 
	Crop::endY = endY;
}
QImage Crop::execute(QImage img,int startX, int startY,int endX, int endY){
	img = img.copy(startX,startY,endX-startX,endY-startY);

	return img;
}
QList<Modifier::proprieteGenerique> Crop::feedCropProperties(int width, int height){
	QList<Modifier::proprieteGenerique> p;

	proprieteGenerique pro;

	pro.name = "debut X";
	pro.min = 0;
	pro.max =  width-1;
	pro.type = "Spinner";
	pro.toolTip = "px";
	p.append(pro);

	pro.name = "debut Y";
	pro.max = height-1;
	p.append(pro);
	
	pro.name= "fin X";
	pro.min = 1;
	pro.max = width;
	p.append(pro);

	pro.name = "fin Y";
	pro.max = height;
	p.append(pro);

	return p;
}

/***Tools***/
Tools::Tools(){
	listOrdreTools = FileManager::readFile(QDir::currentPath() + "/utils/Tools.txt");
}

QList<QString> Tools::getListOrdreTools(){
	return listOrdreTools;
}