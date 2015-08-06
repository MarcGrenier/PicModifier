#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qmainwindow.h>
#include <qclipboard.h>
#include <qactiongroup.h>

#include "OneImageView.h"
#include "MassImageView.h"

#include "FiltreLineaire.h"
#include "FiltreNonLineaire.h"

#include "myLabel.h"

class FilterWindow;

class MainWindow: public QMainWindow
{
	Q_OBJECT
	public:
		MainWindow(QWidget *parent=0 , Qt::WFlags flags =0);
		~MainWindow();
		//methodes initialisant la barre de menu
		void initMenuBar(void);
		void initFileMenu(void);
		void initEditMenu(void);
		void initHelpMenu(void);
		void initFilterMenu(void);
		//methode actualisant du widget afficher dans le centralWidget
		void update(void);

		//methodes apellés pour appliquer un filtre sur l'image dépendant de la situation
		void applyFiltreLineaire(QVector<float> listFact);
		void applyFiltreNonLineaire(QVector<float> listFact);
		void applyResizePixel(int x, int y);
		void applyResizeScale(float ratioX, float ratioY);
		void applyCrop(int x1,int y1, int x2,int y2);
		void applySegmentationCouleur(QVector<int> listFactor);
		void applySegmentationMono(int seuil);
		void applyConvolution(int facteur);
		void MainWindow::applyConvolutionDirectionnelle(QString direction);
		
		//methode appeler pour changer de situation
		void changeState(int newState);
		//active ou désactive les options du menu selon le state
		void disableMenuOption(void);
		
		void clickToSlot(MyLabel *info,char slot);

		//state possible
		enum{
			Loading,
			Started,
			OneImage,
			MassImage
		};

		public slots:
			//action a effectuer selon les actions choisies
			void fileSlot(void);
			void editSlot(void);
			void filterSlot(void);
			void helpSlot(void);


	private :
		//instances des filtre linéaires
		FiltreLineaire filtreLineaire;
		FiltreNonLineaire filtreNonLineaire;
		
		//état du logiciel selon l'enum
		int state;
		QString lastAction;
		//contient le lien vers le presse-papier du système d'exploitation
		QClipboard *clipboard ;
		
		//interfaces
		OneImageView *oneImageView;
		FilterWindow *filterWindow;
		MassImageView *massImageView;

		//aciton group
		QActionGroup *fileAll;
		QActionGroup *fileStarted;
		QActionGroup *fileMass;
		QActionGroup *editAll;
		QActionGroup *editMass;
		QActionGroup *filterAll;

		//menus
		QMenu *fileMenu;
		QMenu *editMenu;
		QMenu *filterMenu;
		QMenu *helpMenu;

		//actions du menu fichier
		QAction *openFileAct;
		QAction *openFolderAct;
		QAction *displayFilterWindowAct;
		QAction *saveAct;
		QAction *saveAsAct;
		QAction *exitAct;

		//actions du menu d'édition
		QAction *copyImageAct;
		QAction *pasteImageAct;
		QAction *resizePixelAct;
		QAction *resizeRatioAct;
		QAction *cropAct;
		QMenu *rotateMenu;
		QAction *rotate90Act;
		QAction *rotate180Act;
		QAction *rotate270Act;
		QAction *mirrorVerticalAct;
		QAction *mirrorHorizontalAct;

		//action du menu filtre
		QMenu *filtreLineaireMenu;
		QMenu *filtreNonLineaireMenu;
		QMenu *segmentationMonoMenu;
		QAction *segmentationMonoGeneriqueAct;
		QAction *segmentationMonoPredefAct;
		QMenu *segmentationCouleurMenu;
		QAction *segmentationCouleurGeneriqueAct;
		QAction *segmentationCouleurPredefAct;
		QMenu *convolutionMenu;
		QMenu *convolutionMoyenneMenu;
		QAction *convolutionMoyennePredefAct;
		QAction *convolutionMoyenneGeneriqueAct;
		QAction *convolutionMoyenneGausienPredefAct;
		QAction *convolutionMoyenneGausienGeneriqueAct;
		QMenu *convolutionDirectionnelleMenu;
		QAction *convolutionDirectionnelleHAct;
		QAction *convolutionDirectionnelleBAct;
		QAction *convolutionDirectionnelleGAct;
		QAction *convolutionDirectionnelleDAct;
		QAction *convolutionDirectionnelleHDAct;
		QAction *convolutionDirectionnelleGDAct;
		QAction *convolutionDirectionnelleBDAct;
		QAction *convolutionDirectionnelleBGAct;


		

		//action du menu d,aide
		QAction *helpAct;

};

#endif