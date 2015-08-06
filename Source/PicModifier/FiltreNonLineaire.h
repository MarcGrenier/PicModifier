#ifndef FILTRENONLINEAIRE_H
#define FILTRENONLINEAIRE_H
#include "Modifier.h"
#include <qvector.h>

class FiltreNonLineaire: public Modifier{
	public:
		FiltreNonLineaire();
		FiltreNonLineaire(QVector<float> factor);
		static QList<Modifier::proprieteGenerique> feedProperties(void);
		static QImage execute(QImage image,QVector<float> listFactor);

		QMap<QString,QVector<float>> getListFiltrePredef(void);
		QList<QString> getListOrdreFiltre(void);

		QVector<float> listFactor;

	private:
		//valeur des filtres prédef
		QMap<QString,QVector<float>> listFiltreNonLineraire;
		QList<QString> listOrdreFiltreNonLineraire;
};
#endif