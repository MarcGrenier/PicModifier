#include "TreeFolder.h"

#include <qfilesystemmodel.h>
#include <qdir.h>
#include <qmessagebox.h>

TreeFolder::TreeFolder(QWidget *parent, int demiWidth,QString actualPath,int height):
	QTreeView(parent)
{
	this->setGeometry(QRect(10, 50, demiWidth-50, height));
	QFileSystemModel *modelFichier = new QFileSystemModel();
	modelFichier->setRootPath(QDir::root().absolutePath());
	modelFichier->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
	this->setModel(modelFichier);
	this->hideColumn(1);
	this->hideColumn(2);
	this->hideColumn(3);

}
QString TreeFolder::getFolderPath(){
	QFileSystemModel *dir = new QFileSystemModel();
	QModelIndex temp = this->currentIndex();

	QString folderPath="";

	while(dir->fileName(temp.parent()) != ""){
		folderPath =  dir->fileName(temp) +"/"+ folderPath;
		temp = temp.parent();
	};

	QString home = dir->fileName(temp);
	if(home.contains('(')){
		home = home.split('(')[1].split(')')[0] + '/';
	}
	else{
		home = home + '/';
	}

	folderPath =  home + folderPath;

	if(!QDir(folderPath).exists() || folderPath == "/"){
		folderPath = "C:/temp/";
		if(!QDir("C:/temp/").exists()){
			QDir().mkdir("C:/temp/");
		}
		QMessageBox::information(this,"Information","Vos images seront sauvegardées dans le dossier C:/temp/");
	}

	return folderPath;

	
}