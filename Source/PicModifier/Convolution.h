#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include "Modifier.h"

class Convolution : public Modifier{
	public :
		Convolution(int facteur,QString type="U");
		static QList<Modifier::proprieteGenerique> feedProperties(void);
		static QImage execute(QImage image,int dimension,QString type = "U");
		static float* generateFactorGrid(int dimension,QString type);
		static QVector<float> getDefaultValue();

		int facteur;
		QString type;
};

#endif