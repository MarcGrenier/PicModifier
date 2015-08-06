#ifndef MASSIMAGEVIEW_H
#define MASSIMAGEVIEW_H

#include <qwidget.h>
#include <qradiobutton.h>
#include <QTextEdit.h>
#include <qlabel.h>
#include <qgroupbox.h>
#include <qtreeview.h>
#include <qlistwidget.h>
#include <qmainwindow.h>
#include <qprogressdialog.h>
#include <qcheckbox.h>


#include "MassImageInterface.h"
#include "TreeFolder.h"

class MassImageView: public QWidget{
	
	Q_OBJECT
	public:
		MassImageView(QMainWindow *parent);
		~MassImageView();
		void display(void);

		void displayFilter(void);
		void displayPreview(void);
		void displayLocation(void);
		void displaySaveOption(void);
		void setFolderPath(QString path);

		void addFilterToList(Modifier *filtre, QString action);
		QString getSaveLocation(void);

		bool openFolder(QWidget *parent);

		void createProcessDialog(void);
		void changeProgressValue(float nbSauvegarder,float nbTotal);

	public slots:
		void removeFilterFromList(void);
		void generatePreview(void);
		void apply(void);
		void endProcess(void);
		
		
	private:
		QMainWindow *mainWindow;
		MassImageInterface massImageInterface;

		bool defaultListElement;

		//divers pour l'affichage
		int width;
		int height;
		int demiWidth;
		int smallHeight;
		
		QFont fontTitle;
		QFont fontTitle1;

		//groupBox
		QGroupBox *filtreGroup;
		QGroupBox *saveGroup;
		//liste affiché à l'écran représentant les filtres à être appliqués
		QListWidget *filterListWidget;

		//image de preview
		QLabel *previewLabel;
		QPixmap imageApercu;
		QPixmap imageApercuStock;

		//vu des dossiers ou sauvegarder
		TreeFolder *treeFolder;

		QRadioButton *radioButton;
		QRadioButton *radioButton_2;
		QRadioButton *radioButton_3;

		QCheckBox *sameFolderBox;

		QTextEdit *fileTemplateName;

		QProgressDialog *progressDialog;

};

#endif