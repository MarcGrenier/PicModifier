#include "FileManager.h"
#include <qvector.h>

QList<QString> FileManager::readFile(QString filePath){

	QFile file(filePath);
	file.open(QIODevice::ReadOnly | QIODevice::Text);

	QTextStream text(&file);

	QList<QString> document;
	while(text.atEnd() == false){
		document.append(text.readLine());
	}

	return document;
}
void FileManager::writeFile(QString filePath, QString text){

}

QMap<QString,QVector<float>> FileManager::textToInfo(QList<QString> listText,int nbElement){
	QMap<QString,QVector<float>> listFiltre;
	QString nomFiltre;
	
	nbElement+=1;
	for(int i =0; i < listText.length() ;i++){
		if(i%nbElement == 0){
			nomFiltre = listText.at(i);
		}
		else{
			listFiltre[nomFiltre].append(listText.at(i).toFloat());
		}
	}

	return listFiltre;

}

QList<QString> FileManager::orderList(QList<QString> listText,int nbElement){
	QList<QString> listFiltre;
	
	nbElement+=1;
	for(int i =0; i < listText.length() ;i++){
		if(i%nbElement == 0){
			listFiltre.push_back(listText.at(i));
		}
	}

	return listFiltre;

}