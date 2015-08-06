#include "MassImageView.h"

#include <qpushbutton.h>
#include <qapplication.h>
#include <qdesktopwidget.h>
#include <qfiledialog.h>
#include <qfilesystemmodel.h>
#include <qtimer.h>

#include "Modifier.h"
#include "MainWindow.h"


MassImageView::MassImageView(QMainWindow *parent)
	:QWidget(parent->centralWidget()),
	fontTitle("Arial",22,QFont::Bold),
	fontTitle1("Arial",18,QFont::Bold),
	smallHeight(225),
	massImageInterface(this)
{
	mainWindow = parent;
	defaultListElement = true;
	imageApercuStock = QPixmap("image/Preview.png");
}
MassImageView::~MassImageView(){
}

bool MassImageView::openFolder(QWidget *parent){
	bool folderWithImage = false;
	massImageInterface.setFolderPath(QFileDialog::getExistingDirectory(parent,"Ouvrir un dossier","/home"));
	
	if(massImageInterface.getFolderPath() != ""){
		QDir folderLocation(massImageInterface.getFolderPath());
		folderLocation.setFilter(QDir::Files);
		QStringList filtres;
		filtres << "*.jpg" << "*.png" << "*.jpeg";
		folderLocation.setNameFilters(filtres);
		QStringList fileList = folderLocation.entryList();
	
		folderWithImage =  massImageInterface.addImages(fileList);
	}

	return folderWithImage;
}

void MassImageView::display(){
	int screenNb = QApplication::desktop()->screenNumber(mainWindow);
	int widthWindow = QApplication::desktop()->screenGeometry(screenNb).width();

	width = QApplication::desktop()->screenGeometry(1).width()- 500;
	height = QApplication::desktop()->height() - 100;

	if(width == 1280-500 && height == 1024-100){
		height=750;
		smallHeight = 125;
	}

	mainWindow->setGeometry(50 + (widthWindow*screenNb),50,width,height);

	height-=50;	

	demiWidth = (width/2)-20;

	displayFilter();
	displayPreview();
	displayLocation();
	displaySaveOption();
}

void MassImageView::displayFilter(void){

	QLabel *folderPathLabel = new QLabel(massImageInterface.getFolderPath(),this);
	folderPathLabel->setGeometry(QRect(10, 2, width, 16));

	filtreGroup = new QGroupBox("Filtre",this);
    filtreGroup->setGeometry(QRect(10, 20, demiWidth, height));	

	QWidget *filterToApplyWidget = new QWidget(filtreGroup);
    filterToApplyWidget->setGeometry(QRect(10, 19, demiWidth-30, (height/2)-100));

    QLabel *filtreToApplyText = new QLabel("Filtre à appliquer",filterToApplyWidget);
    filtreToApplyText->setGeometry(QRect(0, 0, 300, 35));
	filtreToApplyText->setFont(fontTitle);

	filterListWidget = new QListWidget(filterToApplyWidget);
    filterListWidget->setGeometry(QRect(10, 50, demiWidth-50, smallHeight));
	filterListWidget->addItem("aucun filtre");
 
	QPushButton *eraseFilter = new QPushButton("Effacer",filterToApplyWidget);
    eraseFilter->setGeometry(QRect(demiWidth-120, (height/2)-150, 70, 25));
	QObject::connect(eraseFilter,SIGNAL(clicked()),this,SLOT(removeFilterFromList()));

	QFrame *lineFilter = new QFrame(filtreGroup);
    lineFilter->setGeometry(QRect(20, (height/2)-90, demiWidth-40, 20)); 
	lineFilter->setFrameShape(QFrame::HLine);
    lineFilter->setFrameShadow(QFrame::Sunken);
}
void MassImageView::displayPreview(void){
	QWidget *apercuWidget = new QWidget(filtreGroup);
    apercuWidget->setGeometry(QRect(10, (height/2)-90, demiWidth-30, (height/2)+90));

	QLabel *previewTitle = new QLabel("Aperçu",apercuWidget);
    previewTitle->setGeometry(QRect(0, 10, 200, 35));
	previewTitle->setFont(fontTitle);
	
	imageApercu = QPixmap("image/Preview.png");
	
	previewLabel = new QLabel("image",apercuWidget);
	int labelHeight = ((demiWidth-50)*imageApercu.height())/imageApercu.width();
	previewLabel->setGeometry(QRect(10,60,demiWidth-50,labelHeight/*300*/));
	previewLabel->setStyleSheet("border:1px solid black; text-align:center;");
	
	
	previewLabel->setPixmap(imageApercu.scaled(previewLabel->width(),previewLabel->height()));

	QPushButton *generatePreview = new QPushButton("Générer l'aperçu",apercuWidget);
    generatePreview->setGeometry(QRect(demiWidth-200, (height/2)+40, 130, 30));
	QObject::connect(generatePreview, SIGNAL(clicked()),this,SLOT(generatePreview()));
}
void MassImageView::displayLocation(void){
    
	saveGroup = new QGroupBox("Option d'enregistrement",this);
    saveGroup->setGeometry(QRect(demiWidth+20, 20, demiWidth, height));

	QWidget *saveLocationWidget = new QWidget(saveGroup);
    saveLocationWidget->setGeometry(QRect(10, 19, demiWidth-30, (height/2)-100));

	QLabel *saveLocationText = new QLabel("Lieu de la sauvegarde",saveLocationWidget);
    saveLocationText->setGeometry(QRect(0, 0, 400, 28));
	saveLocationText->setFont(fontTitle1);
    
	treeFolder = new TreeFolder(saveLocationWidget,demiWidth,massImageInterface.getFolderPath(),smallHeight);
	
	sameFolderBox = new QCheckBox("Garder le même emplacement",saveLocationWidget);
	sameFolderBox->setGeometry(QRect(10,smallHeight+75,200,sameFolderBox->height()));

	QFrame *lineOption = new QFrame(saveGroup);
	lineOption->setGeometry(QRect(20, (height/2)-90, demiWidth-40, 20));
    lineOption->setFrameShape(QFrame::HLine);
    lineOption->setFrameShadow(QFrame::Sunken);
}
void MassImageView::displaySaveOption(void){
	QWidget *saveOptionWidget = new QWidget(saveGroup);
    saveOptionWidget->setGeometry(QRect(10, (height/2)-90, demiWidth-30, (height/2)+90));
   
	QLabel *saveOptionText = new QLabel("Mode de sauvegarde",saveOptionWidget);
    saveOptionText->setGeometry(QRect(0, 10, 600, 28));
	saveOptionText->setFont(fontTitle1);

	radioButton = new QRadioButton("Même nom",saveOptionWidget);
    radioButton->setGeometry(QRect(40, 80, 200, 16));
	radioButton->setChecked(true);
    
	radioButton_2 = new QRadioButton("Même nom + (chiffre)",saveOptionWidget);
    radioButton_2->setGeometry(QRect(40, 140, 200, 16));

	radioButton_3 = new QRadioButton("Nouveau nom + chiffre",saveOptionWidget);
    radioButton_3->setGeometry(QRect(40, 200, 200, 16));
    
	fileTemplateName = new QTextEdit(saveOptionWidget);
    fileTemplateName->setGeometry(QRect(90, 240, 200, 20));
    fileTemplateName->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	fileTemplateName->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	QPushButton *applyToAllFile = new QPushButton("appliquer", saveOptionWidget);
    applyToAllFile->setGeometry(QRect(demiWidth-260, (height/2)+10, 175, 30));
	QObject::connect(applyToAllFile,SIGNAL(clicked()),this,SLOT(apply()));
    
}

void MassImageView::addFilterToList(Modifier *filtre, QString action){
	if(filterListWidget->item(0)->text() == "aucun filtre"){
		 delete filterListWidget->takeItem(0);
		 defaultListElement = false;
	}

	massImageInterface.addFilterToList(filtre);

	filterListWidget->addItem(action);
}
void MassImageView::removeFilterFromList(void){
	
	if(defaultListElement== false){
		Q_FOREACH(QListWidgetItem *i, filterListWidget->selectedItems()){
			massImageInterface.removeFilterFromList(filterListWidget->row(i));
		}
	}

	qDeleteAll(filterListWidget->selectedItems());
	
	
	if(filterListWidget->count() == 0){
		filterListWidget->addItem("aucun filtre");
		defaultListElement = true;
	}
}

void MassImageView::apply(void){
	createProcessDialog();
	QString folderPath = getSaveLocation();	
	
	if(radioButton->isChecked()){
		massImageInterface.saveAll(folderPath,1,"");
	}
	else if(radioButton_2->isChecked()){
		massImageInterface.saveAll(folderPath,2,"");
	}
	else if(radioButton_3->isChecked()){
		massImageInterface.saveAll(folderPath,3,fileTemplateName->toPlainText());
	}
	QTimer::singleShot(2000, this, SLOT(endProcess()));
}

void MassImageView::generatePreview(void){
	previewLabel->setPixmap((massImageInterface.applyFilter(imageApercuStock)).scaled(previewLabel->width(),previewLabel->height()));
}

QString MassImageView::getSaveLocation(void){
	QString path;
	if(sameFolderBox->isChecked()){
		QDir f = QDir(massImageInterface.getFolderPath());
		path= f.absolutePath();
	}
	else{
		path = treeFolder->getFolderPath();
	}

	return path;
}

void MassImageView::createProcessDialog(void){
	progressDialog =  new QProgressDialog("Progression de la sauvegarde","Annuler",0,100,this);

	progressDialog->setValue(0);
	progressDialog->setMinimumDuration(0);
}

void MassImageView::changeProgressValue(float nbSauvegarder,float nbTotal){
	progressDialog->setValue(nbSauvegarder/nbTotal*100);
}

void MassImageView::endProcess(){
	changeProgressValue(1,1);
}