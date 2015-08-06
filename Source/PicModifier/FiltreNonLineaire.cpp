#include "FiltreNonLineaire.h"
#include "FileManager.h"

#include <qmessagebox.h>
#include <qdir.h>

FiltreNonLineaire::FiltreNonLineaire(){
	QList<QString> text = FileManager::readFile(QDir::currentPath() + "/utils/FiltreNonLineaire.txt");
	listFiltreNonLineraire = FileManager::textToInfo(text,3);
	listOrdreFiltreNonLineraire = FileManager::orderList(text,3);
}

FiltreNonLineaire::FiltreNonLineaire(QVector<float> factor):Modifier(){
	listFactor = factor;
}

QList<Modifier::proprieteGenerique> FiltreNonLineaire::feedProperties(void){
	

	QList<Modifier::proprieteGenerique> propriete;

	proprieteGenerique pro1;
	pro1.max = 255;
	pro1.min = -255;
	pro1.type="DoubleSpiner";
	pro1.name="a1";
	pro1.toolTip="valeur entre -255 et 255";

	proprieteGenerique pro2;
	pro2.max = 128;
	pro2.min = -128;
	pro2.type="DoubleSpiner";
	pro2.name="a2";
	pro2.toolTip="valeur entre [-128,0[ et ]0,128]";

	proprieteGenerique pro3;
	pro3.max = 128;
	pro3.min = 0;
	pro3.type="DoubleSpiner";
	pro3.name="a3";
	pro3.toolTip="valeur entre ]0,128]";

	propriete.append(pro1);
	propriete.append(pro2);
	propriete.append(pro3);


	return propriete;
}
QImage FiltreNonLineaire::execute(QImage image,QVector<float> listFactor){
	
	if(listFactor[2]!=0 && listFactor[1]!=0 ){
		register unsigned char *i;

		i = image.bits();
		register unsigned char *last = i + image.width()*image.height()*4;

		float iFloat;
		while(i<last){
			iFloat = *i;
			*i++ = listFactor[0] + (255*listFactor[1]) * pow((iFloat /255),listFactor[2]);
			iFloat = *i;
			*i++ = listFactor[0] + (255*listFactor[1]) * pow((iFloat /255),listFactor[2]);
			iFloat = *i;
			*i++ = listFactor[0] + (255*listFactor[1]) * pow((iFloat /255),listFactor[2]);

			*i++;
		}
	}
	else{
		QMessageBox msgBox;
		msgBox.setIcon(QMessageBox::Information);
		msgBox.setText("Un des facteurs ne respectait pas les conditions d'utilisations");
		msgBox.setInformativeText("Filtre non linéaire");
		msgBox.exec();
	}
	return image;

}


QMap<QString,QVector<float>> FiltreNonLineaire::getListFiltrePredef(void){
	return listFiltreNonLineraire;
}
QList<QString> FiltreNonLineaire::getListOrdreFiltre(void){
	return listOrdreFiltreNonLineraire;

}