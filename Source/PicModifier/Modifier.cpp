#include "Modifier.h"
#include "FileManager.h"
#include <qdir.h>

Modifier::Modifier(){
	listOrdreFilter = FileManager::readFile(QDir::currentPath() + "/utils/Autre.txt");
}

QList<QString> Modifier::getListOrdreOther(){
	return listOrdreFilter;
}