#include "Utils_Widget.h"

QSlider* Utils_Widget::addSlider(int min,int max,QWidget *parent){
	QSlider *q = new QSlider(Qt::Horizontal,parent);
	q->setRange(min,max);
	return q;
}

QLCDNumber* Utils_Widget::addLcdNumber(QWidget *parent){
	QLCDNumber *lcd = new QLCDNumber(parent);
	lcd->setSegmentStyle(QLCDNumber::Flat);

	return lcd;
}
QDoubleSpinBox* Utils_Widget::addDoubleSpinBox(int min, int max,QWidget *parent){
	QDoubleSpinBox *q = new QDoubleSpinBox(parent);
	q->setRange(min,max);
	q->setSingleStep(0.01);
	q->setAccelerated(true);

	return q;
}

QSpinBox* Utils_Widget::addSpinBox(int min,int max,QWidget *parent){
	QSpinBox *spin = new QSpinBox(parent);
	spin->setRange(min,max);
	spin->setAccelerated(true);

	return spin;
}

QComboBox* Utils_Widget::addComboBox(QWidget *parent,QStringList list){
	QComboBox *combo = new QComboBox(parent);

	combo->addItems(list);

	return combo;
}