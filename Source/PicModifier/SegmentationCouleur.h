#ifndef SEGMENTATIONCOULEUR_H
#define SEGMENTATIONCOULEUR_H
#include "Modifier.h"

class SegmentationCouleur: public Modifier{

	public:
		SegmentationCouleur(QVector<int> seuil);
		static QList<Modifier::proprieteGenerique> feedProperties(void);
		static QImage execute(QImage image,QVector<int> seuil);
		static QVector<float> getDefaultValue(void);
	
		QVector<int> seuil;
};

#endif