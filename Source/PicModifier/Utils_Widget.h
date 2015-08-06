#ifndef UTILS_WIDGET_H
#define UTILS_WIDGET_H
#include <qslider.h>
#include <qlcdnumber.h>
#include <QDoubleSpinBox>
#include <qlineedit.h>
#include <qcombobox.h>

class Utils_Widget{
	public:
		static QSlider* addSlider(int min,int max,QWidget *parent);
		static QLCDNumber* addLcdNumber(QWidget *parent);
		static QDoubleSpinBox* addDoubleSpinBox(int min, int max,QWidget *parent);
		static QLineEdit* addEntry(void);
		static QSpinBox* addSpinBox(int min,int max,QWidget *parent);
		static QComboBox* addComboBox(QWidget *parent,QStringList list);
};

#endif;