#ifndef FILTERWINDOW_H
#define FILTERWINDOW_H

#include <qdialog.h>
#include <qtabwidget.h>
#include <qgroupbox.h>
#include <qslider.h>
#include <qgridlayout.h>
#include <QDoubleSpinBox>
#include <qvector.h>
#include <qscrollarea.h>

#include "Modifier.h"


class MainWindow;

class FilterWindow: public QDialog{

	Q_OBJECT
	public:
		FilterWindow(QWidget *parent , Qt::WFlags flags);
		~FilterWindow();
		//Ajuste la position et la dimmension de la fenêtre et la rend visible
		void display(void);
		void visible(void);
		//ajoute la section de la fenêtre contenant les onglets contenant les filtres et les outils
		void insertTabSection(void);
		//ajoute la section de la fenêtre contenant les propriete des filtes (vide)
		void insertPropertySection(void);
		QScrollArea* insertScrollSection(QList<QString> name, char slot);
		
		// ajout de widget dans la section des propriete
		QSlider* addSlider(QString titre,int min,int max,int row,float value,bool enabled);
		QDoubleSpinBox* addDoubleSpinner(QString titre,int min,int max,int row,float value,bool enabled);
		QSpinBox* addSpinner(QString titre, int min, int max,int row,float value,bool enabled);

		void addApplyButton(int row);

		//Reçoit une liste contenant le nom et les proprietes de chaque options permettant a cette méthode d'appeler
		//		les méthodes add... permettant de construire la liste de propriete de la section de propriete
		void buildPropertyFromFiltre(QList<Modifier::proprieteGenerique> property,QString typeFiltre,QVector<float> value,bool enabled);
		//efface tous les éléments de la section propriétés
		void eraseProperties();
		//méthode appelant les méthode du même nom de la classe Mainwindow appliquant les filtres sur l'image
		void applyFiltreLineaire(void);
		void applyFiltreNonLineaire(void);
		void applyResizeScale(void);
		void applyResizePixel(void);
		void applyCrop(void);
		void applySegmentationMono(void);
		void applySegmentationCouleur(void);
		void applyConvolution(void);

	public slots:
		//slot appeler lorsque le boutton appliquer de la section propriete est pesé
		void applyFilterOrTool(void);
		void toUnpair(int value);

	signals:
		void updateLcd(int value);

	private:
		//dimensions par defaut de la fenêtre par default
		int defaultWidth;
		int defaultHeight;
		
		//widget contenant les onglets
		QTabWidget* tabWidget;

		//widget regroupant les proprietés des filtres
		QGroupBox* proprieteSection;
		//layout contenu dans le QGroupBox des proprietes
		QGridLayout* layout;

		//list de toutes les widget contenant des valeurs de la section propriete
		QList<QWidget*> listPropriete;

		//nom du filtre actuellement affiché dans la section propriete
		QString proprieteFilterActual;

};

#endif