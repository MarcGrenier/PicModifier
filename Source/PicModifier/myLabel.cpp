#include "myLabel.h"

MyLabel::MyLabel(){

}

MyLabel::MyLabel(const QString & text, QWidget * parent):QLabel(text,parent){

}

void MyLabel::mousePressEvent ( QMouseEvent * event ) 
{
	emit clicked();
}