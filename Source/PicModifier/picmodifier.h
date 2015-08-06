#ifndef PICMODIFIER_H
#define PICMODIFIER_H

#include <QtGui/QMainWindow>
#include "ui_picmodifier.h"

class PicModifier : public QMainWindow
{
	Q_OBJECT

public:
	PicModifier(QWidget *parent = 0, Qt::WFlags flags = 0);
	~PicModifier();

private:
	Ui::PicModifierClass ui;
};

#endif // PICMODIFIER_H
