#ifndef SEGMENTATIONMONO_H
#define SEGMENTATIONMONO_H
#include "Modifier.h"
#include <qvector.h>

class SegmentationMono: public Modifier{

	public:
		SegmentationMono(int seuil);
		static QList<Modifier::proprieteGenerique> feedProperties(void);
		static QImage execute(QImage image,int seuil);
		static QVector<float> getDefaultValue(void);

		int seuil;
};
#endif

