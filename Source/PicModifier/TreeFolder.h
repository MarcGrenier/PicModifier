#ifndef TREEFOLDER_H
#define TREEFOLDER_H

#include <qtreeview.h>

class TreeFolder:public QTreeView{

public:
	TreeFolder(QWidget *parent, int demiWidth,QString actualPath,int height);

	QString getFolderPath();
};

#endif