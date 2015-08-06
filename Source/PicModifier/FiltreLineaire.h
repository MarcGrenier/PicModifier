#ifndef FILTRELINEAIRE_H
#define FILTRELINEAIRE_H
#include "Modifier.h"
#include <qvector.h>

class FiltreLineaire: public Modifier{
	public:
		FiltreLineaire();
		FiltreLineaire(QVector<float> factor);
		static QList<Modifier::proprieteGenerique> feedProperties(void);
		static QImage execute(QImage image,QVector<float> listFactor);
		
		QMap<QString,QVector<float>> getListFiltrePredef(void);
		QList<QString> getListOrdreFiltre(void);

		QVector<float> listFactor;

	private:
		//valeur des filtres prédef
		QMap<QString,QVector<float>> listFiltreLineraire;
		QList<QString> listOrdreFiltreLineraire;
		static unsigned char checkOutputValue(float input);
		
};
#endif
