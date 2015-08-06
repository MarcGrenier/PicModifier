#include "picmodifier.h"
#include <qtoolbar.h>

PicModifier::PicModifier(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	QToolBar("allo",this);

}

PicModifier::~PicModifier()
{

}
