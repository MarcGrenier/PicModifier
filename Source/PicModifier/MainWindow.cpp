#include "MainWindow.h"
#include "FilterWindow.h"
#include "FileManager.h"

#include "Tools.h"
#include "SegmentationMono.h"
#include "SegmentationCouleur.h"
#include "Convolution.h"

#include <qapplication.h>
#include <qurl.h>
#include <qmimedata.h>
#include <qmenubar.h>
#include <qfiledialog.h>

MainWindow::MainWindow(QWidget *parent , Qt::WFlags flags): 
QMainWindow(parent,flags),state(Loading),clipboard(QApplication::clipboard())
{
	this->setGeometry(50,50,640,245);
	initMenuBar();
	filterWindow = new FilterWindow(this,flags);
	changeState(Started);
}

MainWindow::~MainWindow(){
}

void MainWindow::changeState(int newState){
	state=newState;
	if(state == OneImage){
		this->setCentralWidget(oneImageView);
	}
	else if (state == MassImage){
		massImageView->display();
		this->setCentralWidget(massImageView);
	}
	disableMenuOption();
}

void MainWindow::disableMenuOption(void){
	QString classType;
	if(state == Started){		
		fileAll->setDisabled(true);
		fileMass->setDisabled(true);
		fileStarted->setEnabled(true);

		filterAll->setDisabled(true);
		editAll->setDisabled(true);
		editMass->setDisabled(true);

	}
	else if(state==OneImage){
		fileAll->setEnabled(true);
		fileMass->setEnabled(true);
		fileStarted->setEnabled(true);


		filterAll->setEnabled(true);
		
		editAll->setEnabled(true);
		editMass->setEnabled(true);
	}
	else if(state==MassImage){
		fileAll->setEnabled(true);
		fileMass->setDisabled(true);
		fileStarted->setEnabled(true);

		filterAll->setEnabled(true);

		editAll->setEnabled(true);
		editMass->setDisabled(true);
	}

}

void MainWindow::initMenuBar(void){
	fileMenu = menuBar()->addMenu("Fichier");
	editMenu = menuBar()->addMenu("Édition");
	filterMenu = menuBar()->addMenu("Filtre");
	helpMenu = menuBar()->addMenu("Aide");

	initFileMenu();
	initEditMenu();
	initFilterMenu();
	initHelpMenu();
}

void MainWindow::initFileMenu(void){
	fileAll = new QActionGroup(this);
	fileStarted = new QActionGroup(this);
	fileMass = new QActionGroup(this);

	openFileAct = new QAction("Ouvrir un fichier",fileMenu);
	openFileAct->setShortcut(QKeySequence::Open);
	QObject::connect(openFileAct,SIGNAL(triggered()),this,SLOT(fileSlot()));

	openFolderAct = new QAction("Ouvrir un dossier",fileMenu);
	QObject::connect(openFolderAct,SIGNAL(triggered()),this,SLOT(fileSlot()));

	displayFilterWindowAct =  new QAction("Fenêtre filtre",fileMenu);
	QObject::connect(displayFilterWindowAct,SIGNAL(triggered()),this,SLOT(fileSlot()));

	saveAct = new QAction("Sauvegarder",fileMenu);
	saveAct->setShortcut(QKeySequence::Save);
	QObject::connect(saveAct,SIGNAL(triggered()),this,SLOT(fileSlot()));

	saveAsAct = new QAction("Sauvegarder sous",fileMenu);
	saveAsAct->setShortcut(QKeySequence::SaveAs);
	QObject::connect(saveAsAct,SIGNAL(triggered()),this,SLOT(fileSlot()));

	exitAct = new QAction("Quitter",fileMenu);
	exitAct->setShortcut(QKeySequence::Close);
	QObject::connect(exitAct,SIGNAL(triggered()),this,SLOT(fileSlot()));

	fileMenu->addAction(openFileAct);
	fileMenu->addAction(openFolderAct);
	fileMenu->addSeparator();
	fileMenu->addAction(saveAct);
	fileMenu->addAction(saveAsAct);
	fileMenu->addSeparator();
	fileMenu->addAction(displayFilterWindowAct);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);

	fileAll->addAction(displayFilterWindowAct);

	fileStarted->addAction(openFileAct);
	fileStarted->addAction(openFolderAct);

	fileMass->addAction(saveAct);
	fileMass->addAction(saveAsAct);
}
void MainWindow::initEditMenu(void){
	editAll = new QActionGroup(this);
	editMass = new QActionGroup(this);

	copyImageAct = new QAction("copier",editMenu);
	copyImageAct->setShortcut(QKeySequence::Copy);
	QObject::connect(copyImageAct,SIGNAL(triggered()),this,SLOT(editSlot()));
	pasteImageAct = new QAction("coller",editMenu);
	pasteImageAct->setShortcut(QKeySequence::Paste);
	QObject::connect(pasteImageAct,SIGNAL(triggered()),this,SLOT(editSlot()));

	resizePixelAct = new QAction("Redimmension par pixel",editMenu);
	QObject::connect(resizePixelAct,SIGNAL(triggered()),this,SLOT(editSlot()));
	resizeRatioAct = new QAction("Redimmension proportionnelle",editMenu);
	QObject::connect(resizeRatioAct,SIGNAL(triggered()),this,SLOT(editSlot()));

	cropAct = new QAction("Rognage",editMenu);
	QObject::connect(cropAct,SIGNAL(triggered()),this,SLOT(editSlot()));

	rotateMenu = new QMenu("Rotation",editMenu);
	rotate90Act = new QAction("90°",rotateMenu);
	QObject::connect(rotate90Act,SIGNAL(triggered()),this,SLOT(editSlot()));
	rotate180Act = new QAction("180°",rotateMenu);
	QObject::connect(rotate180Act,SIGNAL(triggered()),this,SLOT(editSlot()));
	rotate270Act = new QAction("270°",rotateMenu);
	QObject::connect(rotate270Act,SIGNAL(triggered()),this,SLOT(editSlot()));

	mirrorVerticalAct = new QAction("Miroir vertical",editMenu);
	QObject::connect(mirrorVerticalAct,SIGNAL(triggered()),this,SLOT(editSlot()));
	mirrorHorizontalAct = new QAction("Miroir horizontal",editMenu);
	QObject::connect(mirrorHorizontalAct,SIGNAL(triggered()),this,SLOT(editSlot()));

	editAll->addAction(resizeRatioAct);
	editAll->addAction(rotate90Act);
	editAll->addAction(rotate180Act);
	editAll->addAction(rotate270Act);
	editAll->addAction(mirrorVerticalAct);
	editAll->addAction(mirrorHorizontalAct);

	editMass->addAction(resizePixelAct);
	editMass->addAction(cropAct);
	editMass->addAction(pasteImageAct);
	editMass->addAction(copyImageAct);

	editMenu->addAction(copyImageAct);
	editMenu->addAction(pasteImageAct);
	editMenu->addSeparator();
	rotateMenu->addAction(rotate90Act);
	rotateMenu->addAction(rotate180Act);
	rotateMenu->addAction(rotate270Act);
	editMenu->addMenu(rotateMenu);
	editMenu->addSeparator();
	editMenu->addAction(mirrorHorizontalAct);
	editMenu->addAction(mirrorVerticalAct);
	editMenu->addSeparator();
	editMenu->addAction(resizePixelAct);
	editMenu->addAction(resizeRatioAct);
	editMenu->addSeparator();
	editMenu->addAction(cropAct);
}
void MainWindow::initFilterMenu(void){
	filterAll = new QActionGroup(this);
	/*******filtre linéaire******/
	//menu
	filtreLineaireMenu = new QMenu("filtre linéaire",filterMenu);
	QAction *filtre;
	QList<QString> ordre = filtreLineaire.getListOrdreFiltre();
	for(int k=0;k<ordre.length();k++){
		//action
		filtre = new QAction(ordre.at(k),filtreLineaireMenu);
		//connect
		QObject::connect(filtre,SIGNAL(triggered()),this,SLOT(filterSlot()));
		filtreLineaireMenu->addAction(filtre);
		filterAll->addAction(filtre);
		if(k== 0 || ordre.at(k) == "Assombrissement relatif 25.0 %"){
			filtreLineaireMenu->addSeparator();
		}
	}
	/******filtre non linéaire******/
	//menu
	filtreNonLineaireMenu = new QMenu("filtre non linéaire",filterMenu);
	ordre = filtreNonLineaire.getListOrdreFiltre();
	for(int k=0;k<ordre.length();k++){
		//action
		filtre = new QAction(ordre.at(k),filtreNonLineaireMenu);
		//connect
		QObject::connect(filtre,SIGNAL(triggered()),this,SLOT(filterSlot()));
		filtreNonLineaireMenu->addAction(filtre);
		filterAll->addAction(filtre);
		if(k== 0 || k ==6){
			filtreNonLineaireMenu->addSeparator();
		}
	}
	/*******segmentation monochrome******/
	//menu
	segmentationMonoMenu = new QMenu("Segmentation monochrome",filterMenu);
	//action
	segmentationMonoGeneriqueAct = new QAction("Segmentation monochrome générique",segmentationMonoMenu);
	segmentationMonoPredefAct = new QAction("Segmentation monochrome prédéfinie",segmentationMonoMenu);
	//connect
	QObject::connect(segmentationMonoGeneriqueAct,SIGNAL(triggered()),this,SLOT(filterSlot()));
	QObject::connect(segmentationMonoPredefAct,SIGNAL(triggered()),this,SLOT(filterSlot()));
	
	segmentationMonoMenu->addAction(segmentationMonoGeneriqueAct);
	segmentationMonoMenu->addAction(segmentationMonoPredefAct);
	filterAll->addAction(segmentationMonoGeneriqueAct);
	filterAll->addAction(segmentationMonoPredefAct);

	/******segmentation couleur********/
	//menu
	segmentationCouleurMenu = new QMenu("Segmentation par couleur",filterMenu);
	//action
	segmentationCouleurGeneriqueAct = new QAction("Segmentation par couleur générique",segmentationCouleurMenu);
	segmentationCouleurPredefAct = new QAction("Segmentation par couleur prédéfinie",segmentationCouleurMenu);
	//connect
	QObject::connect(segmentationCouleurGeneriqueAct,SIGNAL(triggered()),this,SLOT(filterSlot()));
	QObject::connect(segmentationCouleurPredefAct,SIGNAL(triggered()),this,SLOT(filterSlot()));


	segmentationCouleurMenu->addAction(segmentationCouleurGeneriqueAct);
	segmentationCouleurMenu->addAction(segmentationCouleurPredefAct);
	filterAll->addAction(segmentationCouleurGeneriqueAct);
	filterAll->addAction(segmentationCouleurPredefAct);

	/*****convolution*****/
	//menu
	convolutionMenu = new QMenu("Convolution",filterMenu);
	//1er sous-menu
	convolutionMoyenneMenu = new QMenu("Moyenneur",convolutionMenu);	
	convolutionMenu->addMenu(convolutionMoyenneMenu);
		//action
	convolutionMoyennePredefAct = new QAction("Uniforme prédéfinie",convolutionMoyenneMenu);
	convolutionMoyenneGeneriqueAct = new QAction("Uniforme générique",convolutionMoyenneMenu);
	filterAll->addAction(convolutionMoyennePredefAct);
	filterAll->addAction(convolutionMoyenneGeneriqueAct);
		//connect
	QObject::connect(convolutionMoyennePredefAct,SIGNAL(triggered()),this,SLOT(filterSlot()));
	QObject::connect(convolutionMoyenneGeneriqueAct,SIGNAL(triggered()),this,SLOT(filterSlot()));
	//2e sous-menu
		//action
	convolutionMoyenneGausienPredefAct = new QAction("Gausien prédéfinie",convolutionMoyenneMenu);
	convolutionMoyenneGausienGeneriqueAct = new QAction("Gausien générique",convolutionMoyenneMenu);
	convolutionMoyenneGausienPredefAct->setDisabled(true);
	convolutionMoyenneGausienGeneriqueAct->setDisabled(true);
	filterAll->addAction(convolutionMoyenneGausienPredefAct);
	filterAll->addAction(convolutionMoyenneGausienGeneriqueAct);
		//connect
	QObject::connect(convolutionMoyenneGausienPredefAct,SIGNAL(triggered()),this,SLOT(filterSlot()));
	QObject::connect(convolutionMoyenneGausienGeneriqueAct,SIGNAL(triggered()),this,SLOT(filterSlot()));

	convolutionMoyenneMenu->addAction(convolutionMoyenneGeneriqueAct);
	convolutionMoyenneMenu->addAction(convolutionMoyennePredefAct);
	filterAll->addAction(filtre);
	convolutionMoyenneMenu->addSeparator();
	convolutionMoyenneMenu->addAction(convolutionMoyenneGausienGeneriqueAct);
	convolutionMoyenneMenu->addAction(convolutionMoyenneGausienPredefAct);

	//3e sous-menu
	convolutionDirectionnelleMenu = new QMenu("Directionnelle",convolutionMenu);
	convolutionMenu->addMenu(convolutionDirectionnelleMenu);
		//action
	convolutionDirectionnelleHAct  = new QAction("Haut",convolutionDirectionnelleMenu);
	convolutionDirectionnelleBAct  = new QAction("Bas",convolutionDirectionnelleMenu);
	convolutionDirectionnelleGAct  = new QAction("Gauche",convolutionDirectionnelleMenu);
	convolutionDirectionnelleDAct  = new QAction("Droite",convolutionDirectionnelleMenu);
	convolutionDirectionnelleHDAct = new QAction("Haut-Droite",convolutionDirectionnelleMenu);
	convolutionDirectionnelleGDAct = new QAction("Haut-Gauche",convolutionDirectionnelleMenu);
	convolutionDirectionnelleBDAct = new QAction("Bas-Droite",convolutionDirectionnelleMenu);
	convolutionDirectionnelleBGAct = new QAction("Bas-Gauche",convolutionDirectionnelleMenu);
		//connect
	QObject::connect(convolutionDirectionnelleHAct ,SIGNAL(triggered()),this,SLOT(filterSlot()));
	QObject::connect(convolutionDirectionnelleBAct ,SIGNAL(triggered()),this,SLOT(filterSlot()));
	QObject::connect(convolutionDirectionnelleGAct ,SIGNAL(triggered()),this,SLOT(filterSlot()));
	QObject::connect(convolutionDirectionnelleDAct ,SIGNAL(triggered()),this,SLOT(filterSlot()));
	QObject::connect(convolutionDirectionnelleHDAct,SIGNAL(triggered()),this,SLOT(filterSlot()));
	QObject::connect(convolutionDirectionnelleGDAct,SIGNAL(triggered()),this,SLOT(filterSlot()));
	QObject::connect(convolutionDirectionnelleBDAct,SIGNAL(triggered()),this,SLOT(filterSlot()));
	QObject::connect(convolutionDirectionnelleBGAct,SIGNAL(triggered()),this,SLOT(filterSlot()));

	convolutionDirectionnelleMenu->addAction(convolutionDirectionnelleHAct);  
	convolutionDirectionnelleMenu->addAction(convolutionDirectionnelleBAct); 
	convolutionDirectionnelleMenu->addAction(convolutionDirectionnelleGAct); 
	convolutionDirectionnelleMenu->addAction(convolutionDirectionnelleDAct);  
	convolutionDirectionnelleMenu->addAction(convolutionDirectionnelleHDAct); 
	convolutionDirectionnelleMenu->addAction(convolutionDirectionnelleGDAct); 
	convolutionDirectionnelleMenu->addAction(convolutionDirectionnelleBDAct);
	convolutionDirectionnelleMenu->addAction(convolutionDirectionnelleBGAct);
	filterAll->addAction(convolutionDirectionnelleHAct);
	filterAll->addAction(convolutionDirectionnelleBAct);
	filterAll->addAction(convolutionDirectionnelleGAct);
	filterAll->addAction(convolutionDirectionnelleDAct);
	filterAll->addAction(convolutionDirectionnelleHDAct);
	filterAll->addAction(convolutionDirectionnelleGDAct);
	filterAll->addAction(convolutionDirectionnelleBDAct);
	filterAll->addAction(convolutionDirectionnelleBGAct);

	filterMenu->addMenu(filtreLineaireMenu);
	filterMenu->addMenu(filtreNonLineaireMenu);
	filterMenu->addSeparator();
	filterMenu->addMenu(segmentationMonoMenu);
	filterMenu->addMenu(segmentationCouleurMenu);
	filterMenu->addSeparator();
	filterMenu->addMenu(convolutionMenu);
}
void MainWindow::initHelpMenu(void){
	helpAct = new QAction("Aide",this);
	helpAct->setShortcut(QKeySequence::HelpContents);
	helpMenu->addAction(helpAct);
	QObject::connect(helpAct,SIGNAL(triggered()),this,SLOT(helpSlot()));
}

void MainWindow::fileSlot(void){
	QAction *sender = dynamic_cast<QAction*>(QObject::sender());
	
	if(sender->text()== "Ouvrir un fichier"){
		oneImageView = new OneImageView(this);
		if(oneImageView->openFile(this) == true){
			changeState(OneImage);
			filterWindow->display();
		}
	}
	else if (sender->text()== "Ouvrir un dossier"){
		massImageView =  new MassImageView(this);
		if(massImageView->openFolder(this) == true){
			changeState(MassImage);
			filterWindow->display();
			
		}
	}
	else if (sender->text()== "Fenêtre filtre"){
		filterWindow->visible();
	}
	else if (sender->text()== "Sauvegarder"){
		if(state == OneImage){
			oneImageView->saveCurrentImage();
		}	
	}
	else if (sender->text()== "Sauvegarder sous"){
		if(state == OneImage){
			oneImageView->saveAsCurrentImage(QFileDialog::getSaveFileName(this,"Sauvegarder une image",oneImageView->getFilePath(),"Images (*.png; *.jpg)"));
		}
	}
	else if (sender->text()== "Quitter"){
		this->close();
	}

}
void MainWindow::editSlot(void){
	QString text = "";
	QString classname= typeid(*QObject::sender()).name();

	if(classname == "class MyLabel"){
		text = dynamic_cast<MyLabel*>(QObject::sender())->toolTip();
	}
	else{
		QAction *sender = dynamic_cast<QAction*>(QObject::sender());
		text = sender->text();
	}
	
	if(text == "copier"){
		lastAction = "copier";
		if(state == OneImage){
			clipboard->setPixmap(oneImageView->imageToQPixmap(oneImageView->getImage())); 
		}
	}
	else if (text== "coller"){		
		lastAction = "coller";

		if( state== Started ){
			const QMimeData *temp = clipboard->mimeData();
			if(temp->hasImage()){
				oneImageView = new OneImageView(this);
				changeState(OneImage);	
				oneImageView->newImage(clipboard->image());
				filterWindow->display();
			}
			else if(temp->hasUrls()){
				QList<QUrl> tempo =  temp->urls();
				oneImageView = new OneImageView(this);
				changeState(OneImage);	
				oneImageView->newImage(tempo.first().toLocalFile());
				filterWindow->display();
			}
		}
		else if(state == OneImage){
			const QMimeData *temp = clipboard->mimeData();
			if(temp->hasImage()){
				oneImageView->newImage(clipboard->image());
				
			}
			else if(temp->hasUrls()){
				QList<QUrl> tempo =  temp->urls();
				oneImageView->newImage(tempo.first().toLocalFile());
			}
		}

	}
	else if (text== "Redimmension par pixel"){
		lastAction = "Redimmension par pixel";
		filterWindow->visible();
		QImage temp = oneImageView->getImage();
		QVector<float> value;
		value << temp.width() << temp.height();
		filterWindow->buildPropertyFromFiltre(ResizePixel::feedResizePixelProperties(),"resize pixel",value,true);
	}
	else if (text== "Redimmension proportionnelle"){
		lastAction = "Redimmension proportionnelle";
		filterWindow->visible();
		filterWindow->buildPropertyFromFiltre(ResizeScale::feedResizeScaleProperties(),"resize scale",ResizeScale::getDefaultValueResizeScale(),true);
	}
	else if (text== "Rognage"){
		lastAction = "Rognage";
		filterWindow->visible();
		QImage temp = oneImageView->getImage();
		QVector<float> value;
		value << 0 << 0 << temp.width() << temp.height();
		filterWindow->buildPropertyFromFiltre(Crop::feedCropProperties(oneImageView->getImage().width(),oneImageView->getImage().height()),"crop",value,true);
	}
	else if (text== "90°"){
		lastAction = "Rotation 90°";
		if(state == OneImage){
			oneImageView->newImage(Rotation::execute(oneImageView->getImage(),1));
		}
		else if(state == MassImage){
			massImageView->addFilterToList(new Rotation(1),lastAction);
		}
	}
	else if (text== "180°"){
		lastAction = "Rotation 180°";
		if(state == OneImage){
			oneImageView->newImage(Rotation::execute(oneImageView->getImage(),2));	
		}
		else if(state == MassImage){
			massImageView->addFilterToList(new Rotation(2),lastAction);
		}
	}
	else if (text== "270°"){
		lastAction = "Rotation 270°";
		if(state == OneImage){
			oneImageView->newImage(Rotation::execute(oneImageView->getImage(),3));
		}
		else if(state == MassImage){
			massImageView->addFilterToList(new Rotation(3),lastAction);
		}
	}
	else if (text== "Miroir vertical"){
		lastAction = "Miroir vertical";
		if(state == OneImage){
			oneImageView->newImage(Miroir::execute(oneImageView->getImage(),'V'));
		}
		else if(state == MassImage){
			massImageView->addFilterToList(new Miroir('V'),lastAction);
		}
	}
	else if (text== "Miroir horizontal"){
		lastAction = "Miroir horizontal";
		if(state == OneImage){
			oneImageView->newImage(Miroir::execute(oneImageView->getImage(),'H'));
		}
		else if(state == MassImage){
			massImageView->addFilterToList(new Miroir('H'),lastAction);
		}
	}

}
void MainWindow::filterSlot(void){
	QString text = "";
	QString classname= typeid(*QObject::sender()).name();

	if(classname == "class MyLabel"){
		text = dynamic_cast<MyLabel*>(QObject::sender())->toolTip();
	}
	else{
		QAction *sender = dynamic_cast<QAction*>(QObject::sender());
		text = sender->text();
	}

	filterWindow->visible();
	//segmentation
	if(text =="Segmentation par couleur générique"){
		lastAction = "Segmentation par couleur générique";
		filterWindow->buildPropertyFromFiltre(SegmentationCouleur::feedProperties(),"segmentationCouleur",SegmentationCouleur::getDefaultValue(),true);
	}
	else if (text == "Segmentation par couleur prédéfinie"){
		lastAction = "Segmentation par couleur prédéfinie";
		filterWindow->buildPropertyFromFiltre(SegmentationCouleur::feedProperties(),"segmentationCouleur",SegmentationCouleur::getDefaultValue(),false);
	}
	else if (text == "Segmentation monochrome générique"){
		lastAction = "Segmentation monochrome générique";
		filterWindow->buildPropertyFromFiltre(SegmentationMono::feedProperties(),"segmentationMonochrome",SegmentationMono::getDefaultValue(),true);
	}
	else if (text == "Segmentation monochrome prédéfinie"){
		lastAction = "Segmentation monochrome prédéfinie";
		filterWindow->buildPropertyFromFiltre(SegmentationMono::feedProperties(),"segmentationMonochrome",SegmentationMono::getDefaultValue(),false);
	}
	//convolution
	else if(text.contains("Uniforme")){
		bool disable = true;
		
		if(text == "Uniforme prédéfinie"){
			lastAction = "convolution uniforme prédéfinie";
			disable=false;
		}
		else{
			lastAction = "convolution uniforme générique";
		}

		filterWindow->buildPropertyFromFiltre(Convolution::feedProperties(),"ConvolutionUni",Convolution::getDefaultValue(),disable);

	}
	else if(text.contains("Gausien")){
		bool disable = true;
		
		if(text == "Gausien prédéfinie"){
			lastAction = "convolution gausien prédéfinie";
			disable=false;
		}
		else{
			lastAction = "convolution gausien générique";
		}

		filterWindow->buildPropertyFromFiltre(Convolution::feedProperties(),"ConvolutionGausien",Convolution::getDefaultValue(),disable);
	}
	else if(text == "Haut"){
		lastAction = "Convolution directionnelle vers le haut";
		applyConvolutionDirectionnelle("N");
	}
	else if(text == "Bas"){
		lastAction = "Convolution directionnelle vers le bas";
		applyConvolutionDirectionnelle("S");
	}
	else if(text == "Gauche"){
		lastAction = "Convolution directionnelle vers la gauche";
		applyConvolutionDirectionnelle("W");
	}
	else if(text == "Droite"){
		lastAction = "Convolution directionnelle vers la droite";
		applyConvolutionDirectionnelle("E");
	}
	else if(text == "Haut-Droite"){
		lastAction = "Convolution directionnelle en haut à droite";
		applyConvolutionDirectionnelle("NE");
	}
	else if(text == "Haut-Gauche"){
		lastAction = "Convolution directionnelle en haut à gauche";
		applyConvolutionDirectionnelle("NW");
	}
	else if(text == "Bas-Droite"){
		lastAction = "Convolution directionnelle en bas à droite";
		applyConvolutionDirectionnelle("SE");
	}
	else if(text == "Bas-Gauche"){
		lastAction = "Convolution directionnelle en bas à gauche";
		applyConvolutionDirectionnelle("SW");
	}
	//filtre linéaire et non linéaire
	else if(text == "Filtre non linéaire générique"){
		lastAction = "filtre non linéaire générique";
		filterWindow->buildPropertyFromFiltre(FiltreNonLineaire::feedProperties(),"filtreNonLineaire",filtreNonLineaire.getListFiltrePredef()[text],true);
	}
	else if(text == "Filtre linéaire générique" ){
		lastAction = "filtre linéaire générique";
		filterWindow->buildPropertyFromFiltre(FiltreLineaire::feedProperties(),"filtreLineaire",filtreLineaire.getListFiltrePredef()[text],true);
	}
	else{
		lastAction = "filtre : " + text;
		if(filtreLineaire.getListFiltrePredef().contains(text)){
			filterWindow->buildPropertyFromFiltre(FiltreLineaire::feedProperties(),"filtreLineaire",filtreLineaire.getListFiltrePredef()[text],false);
		}
		else if(filtreNonLineaire.getListFiltrePredef().contains(text)){
			filterWindow->buildPropertyFromFiltre(FiltreNonLineaire::feedProperties(),"filtreNonLineaire",filtreNonLineaire.getListFiltrePredef()[text],false);
		}
	}

}
void MainWindow::helpSlot(void){
	QDialog *help= new QDialog();
	QList<QString> helpText = FileManager::readFile(QDir::currentPath() + "/utils/Read_Me.txt");
	QString leText = "";
	for(int i=0; i<helpText.count();i++){
		leText += helpText[i] + '\n';
	}
	QTextEdit *t= new QTextEdit(help);
	t->setGeometry(0,0,900,600);
	t->setAcceptRichText(false);
	t->setReadOnly(true);
	QTextDocument *doc = new QTextDocument(leText,t);
	t->setDocument(doc);
	help->show();
}

void MainWindow::applyFiltreLineaire(QVector<float> listFact){
	if(state==OneImage){
		oneImageView->newImage(FiltreLineaire::execute(oneImageView->getImage(),listFact));
	}
	else if(state==MassImage){
		massImageView->addFilterToList(new FiltreLineaire(listFact),lastAction);
	}
}

void MainWindow::applyFiltreNonLineaire(QVector<float> listFact){
	if(state==OneImage){
		oneImageView->newImage(FiltreNonLineaire::execute(oneImageView->getImage(),listFact));
	}
	else if(state==MassImage){
		massImageView->addFilterToList(new FiltreNonLineaire(listFact),lastAction);
	}
}

void MainWindow::applyResizePixel(int x, int y){
	if(state==OneImage){
		oneImageView->newImage(ResizePixel::execute(oneImageView->getImage(),x,y));
	}
	else if(state==MassImage){
		massImageView->addFilterToList(new ResizePixel(x,y),lastAction);
	}
}

void MainWindow::applyResizeScale(float ratioX, float ratioY){
	if(state==OneImage){
		oneImageView->newImage(ResizeScale::execute(oneImageView->getImage(),ratioX,ratioY));
	}
	else if(state==MassImage){
		massImageView->addFilterToList(new ResizeScale(ratioX,ratioY),lastAction);
	}
}

void MainWindow::applyCrop(int x1,int y1, int x2,int y2){
	if(state==OneImage){
		oneImageView->newImage(Crop::execute(oneImageView->getImage(),x1,y1,x2,y2));
	}
	else if(state==MassImage){
		massImageView->addFilterToList(new Crop(x1,y1,x2,y2),lastAction);
	}
}

void MainWindow::applySegmentationMono(int seuil){
	if(state==OneImage){
		oneImageView->newImage(SegmentationMono::execute(oneImageView->getImage(),seuil));
	}
	else if(state==MassImage){
		massImageView->addFilterToList(new SegmentationMono(seuil),lastAction);
	}
}

void MainWindow::applySegmentationCouleur(QVector<int> listFactor){
	if(state==OneImage){
		oneImageView->newImage(SegmentationCouleur::execute(oneImageView->getImage(),listFactor));
	}
	else if(state==MassImage){
		massImageView->addFilterToList(new SegmentationCouleur(listFactor),lastAction);
	}
}

void MainWindow::applyConvolution(int facteur){
	if(state==OneImage){
		oneImageView->newImage(Convolution::execute(oneImageView->getImage(),facteur));
	}
	else if(state==MassImage){
		massImageView->addFilterToList(new Convolution(facteur),lastAction);
	}
}

void MainWindow::applyConvolutionDirectionnelle(QString direction){
	
	if(state==OneImage){
		oneImageView->newImage(FiltreLineaire::execute(oneImageView->getImage(),filtreLineaire.getListFiltrePredef()["Moyenne arithmétique"]));
		oneImageView->newImage(Convolution::execute(oneImageView->getImage(),3,direction));
	}
	else if(state==MassImage){
		massImageView->addFilterToList(new FiltreLineaire(filtreLineaire.getListFiltrePredef()["Moyenne arithmétique"]),"Moyenne arithmétique");
		massImageView->addFilterToList(new Convolution(3,direction),lastAction);
	}
}

void MainWindow::clickToSlot(MyLabel *info, char slot){
	if(slot == 'F'){
		QObject::connect(info,SIGNAL(clicked()),this,SLOT(filterSlot()));
	}
	else if(slot == 'T'){
		QObject::connect(info,SIGNAL(clicked()),this,SLOT(editSlot()));
	}
}