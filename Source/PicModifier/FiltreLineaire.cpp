#include "FiltreLineaire.h"
#include "FileManager.h"

#include <qdir.h>

FiltreLineaire::FiltreLineaire(){

	QList<QString> text = FileManager::readFile(QDir::currentPath() + "/utils/filtreLineaire.txt");
	listFiltreLineraire = FileManager::textToInfo(text,12);
	listOrdreFiltreLineraire = FileManager::orderList(text,12);
}

FiltreLineaire::FiltreLineaire(QVector<float> factor):Modifier(){
	listFactor = factor;
}

QList<Modifier::proprieteGenerique> FiltreLineaire::feedProperties(void){

	QList<Modifier::proprieteGenerique> p;
	proprieteGenerique propri;
	propri.type = "DoubleSpiner";
	propri.max = 255;
	propri.min = -255;
	propri.toolTip="valeur entre -255 et 255";

	
	for(int k =1;k<13;k++){
		propri.name = "a" + QString::number(k);

		p.append(propri);
	}


	return p;
}
QImage FiltreLineaire::execute(QImage image, QVector<float> listFact){
	register unsigned char *i;
	
	i = image.bits();
	register unsigned char *last = i + image.width()*image.height()*4;

	int nbcase =image.width()*image.height();

	//unsigned char *r = new unsigned char[sizeof(unsigned char)*nbcase];
	//unsigned char *g = new unsigned char[sizeof(unsigned char)*nbcase];
	//unsigned char *b= new unsigned char [sizeof(unsigned char)*nbcase];	
	register unsigned char r,g,b;

	while (i < last) {
		b = *i;
		g = *(i+1);
		r = *(i+2);
		
		*i++ = checkOutputValue(listFact[8] + (listFact[9]*(r)) +(listFact[10]*(g)) +(listFact[11]*(b)));
		*i++ = checkOutputValue(listFact[4] + (listFact[5]*(r)) +(listFact[6]*(g)) +(listFact[7]*(b)));
		*i++ = checkOutputValue(listFact[0] + (listFact[1]*(r)) +(listFact[2]*(g)) +(listFact[3]*(b)));		
		*i++;

	}
	r=0;g=0;b=0;

	//delete r;
	//delete g;
	//delete b;

	return image;
}

QMap<QString,QVector<float>> FiltreLineaire::getListFiltrePredef(void){
	return listFiltreLineraire;
}

QList<QString> FiltreLineaire::getListOrdreFiltre(void){
	return listOrdreFiltreLineraire;
}

inline unsigned char FiltreLineaire::checkOutputValue(float input){
	if(input<0.0f){
		return 0;
	}
	else if(input >255.0f){
		return 255;
	}
	
	return input;
}