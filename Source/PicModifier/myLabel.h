#ifndef MYLABEL_H
#define MYLABEL_H

#include <qlabel.h>

class MyLabel: public QLabel{

	Q_OBJECT
public:
		MyLabel();
		MyLabel(const QString & text, QWidget * parent=(QWidget*)0);
protected:
		void mousePressEvent ( QMouseEvent * event );
signals:
		void clicked();	
			
};

#endif