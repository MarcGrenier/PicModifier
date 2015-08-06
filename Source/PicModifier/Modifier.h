#ifndef MODIFIER_H
#define MODIFIER_H

#include <qmap.h>
#include <qimage.h>

class Modifier{
	public:
		Modifier();
		struct proprieteGenerique{
			QString name;
			QString type;
			int max;
			int min;
			QString toolTip;
		};
		virtual ~Modifier(){}
	
		QList<QString> getListOrdreOther();
	private:
		QList<QString> listOrdreFilter;
};

#endif