#include "FilterWindow.h"
#include "MainWindow.h"
#include "Utils_Widget.h"
#include "myLabel.h"
#include "Tools.h"

#include <qlabel.h>
#include <qlcdnumber.h>
#include <qpushbutton.h>
#include <qtooltip.h>


FilterWindow::FilterWindow(QWidget *parent , Qt::WFlags flags) : QDialog(parent)
{	
	defaultHeight = 768;
	defaultWidth = 360;
	this->setFixedSize(defaultWidth,defaultHeight);
	this->setWindowTitle("Filtre");
	insertTabSection();
	insertPropertySection();
}

FilterWindow::~FilterWindow(){
	eraseProperties();
}

void FilterWindow::display(void){
	MainWindow *parent = dynamic_cast<MainWindow*>(this->parent());
	int posX = parent->pos().x() +parent->width() + 40;
	int posY = parent->pos().y() + 35;
	this->setGeometry(posX,posY,0,0);
	this->show();
}

void FilterWindow::visible(void){
	if(!isVisible()){
		setVisible(true);
	}
}

void FilterWindow::insertTabSection(void){
	tabWidget = new QTabWidget(this);
	tabWidget->resize(defaultWidth,defaultHeight/2);
	tabWidget->show();

	FiltreLineaire f;
	FiltreNonLineaire fn;
	Tools t;
	Modifier m;

	tabWidget->addTab(insertScrollSection(f.getListOrdreFiltre(),'F'),"Filtre linéraire");
	tabWidget->addTab(insertScrollSection(fn.getListOrdreFiltre(),'F'),"Filtre non linéraire");
	tabWidget->addTab(insertScrollSection(t.getListOrdreTools(),'T'),"Outils");
	tabWidget->addTab(insertScrollSection(m.getListOrdreOther(),'F'),"Autre filtre");
}

QScrollArea* FilterWindow::insertScrollSection(QList<QString> name, char slot){
	QScrollArea* scrollRegion = new QScrollArea;
	scrollRegion->setBackgroundRole(QPalette::Dark);

	int hauteur = ((name.count()/3)+1 )* 90;

	QWidget *tabFiltreLineraire = new QWidget;
	scrollRegion->setBackgroundRole(QPalette::Dark);
	tabFiltreLineraire->resize(defaultWidth-30,hauteur);
	scrollRegion->setWidget(tabFiltreLineraire);

	QGridLayout *gl = new QGridLayout(tabFiltreLineraire);
	tabFiltreLineraire->setLayout(gl);

	QWidget *temp;
	QGridLayout *l;
	MyLabel *la;
	QPixmap pix;
	MyLabel *info;
	
	int p=0,k=0;
	for(int i=0;i<name.count();i++){

		temp = new QWidget();
		l = new QGridLayout(temp);
		temp->setLayout(l);
			
		la =  new MyLabel();
		pix = QPixmap("image/"+name[i] +".png").scaled(60,60);
		
		if(pix.isNull()){
			pix = QPixmap("image/Sample.png").scaled(60,60);
		}

		la->setPixmap(pix);
		la->setToolTip(name[i]);

		info = new MyLabel(name[i]);
		info->setToolTip(name[i]);

		dynamic_cast<MainWindow*>(this->parent())->clickToSlot(la,slot);
		dynamic_cast<MainWindow*>(this->parent())->clickToSlot(info,slot);

		l->addWidget(la,0,0,Qt::AlignHCenter);
		l->addWidget(info,1,0,Qt::AlignHCenter);

		gl->addWidget(temp,p,k,Qt::AlignTop);
		
		if(i%3 == 2){
			p++;
			k =0;
		}
		else{
			k++;
		}
		
	}

	return scrollRegion;

}

void FilterWindow::insertPropertySection(void){
	proprieteSection = new QGroupBox("Propriété",this);
	proprieteSection->setGeometry(0,defaultHeight/2 +1,defaultWidth,defaultHeight/2);
	proprieteSection->show();

	layout= new QGridLayout(proprieteSection);
	proprieteSection->setLayout(layout);
}

QSlider* FilterWindow::addSlider(QString titre,int min,int max,int row,float value,bool enabled){
	QLabel *l= new QLabel(titre);
	
	QSlider *q = Utils_Widget::addSlider(min,max,proprieteSection);

	q->setValue(value);
	q->setEnabled(enabled);

	if(proprieteFilterActual.contains("Convolution")){
		q->setSingleStep(50);
	}

	QLCDNumber *lcd = Utils_Widget::addLcdNumber(proprieteSection);
	lcd->display(value);
	QObject::connect(q,SIGNAL(valueChanged(int)),this,SLOT(toUnpair(int)));
	QObject::connect(this,SIGNAL(updateLcd(int)),lcd,SLOT(display(int)));
	
	layout->addWidget(l,row,0);
	layout->addWidget(q,row,1); 
	layout->addWidget(lcd,row,2);

	return q;
}

void FilterWindow::toUnpair(int value){
	if(value%2 == 0){
		value-=1;
	}
	emit updateLcd(value);
}

QSpinBox* FilterWindow::addSpinner(QString titre, int min, int max,int row,float value,bool enabled){
	QLabel *l= new QLabel(titre);

	QSpinBox *q = Utils_Widget::addSpinBox(min,max,proprieteSection);
	q->setValue(value);
	q->setEnabled(enabled);

	layout->addWidget(l,row,0);
	layout->addWidget(q,row,1); 
	return q;
	
}

QDoubleSpinBox* FilterWindow::addDoubleSpinner(QString titre,int min,int max,int row,float value,bool enabled){
	QLabel *l= new QLabel(titre);

	QDoubleSpinBox *q = Utils_Widget::addDoubleSpinBox(min,max,proprieteSection);
	q->setValue(value);
	q->setEnabled(enabled);

	layout->addWidget(l,row,0);
	layout->addWidget(q,row,1); 
	return q; 
}

void FilterWindow::buildPropertyFromFiltre(QList<Modifier::proprieteGenerique> propriete, QString typeFiltre,QVector<float> value,bool enabled){
	
	if(layout->count() > 0){
		eraseProperties();
	}

	int i = 0 ;
	proprieteFilterActual = typeFiltre;

	Q_FOREACH(Modifier::proprieteGenerique p,propriete){
		QWidget *temp;
		if(p.type == "DoubleSpiner"){
			temp = addDoubleSpinner(p.name,p.min,p.max,i,value[i],enabled);	
		}
		else if(p.type == "Spinner"){
			temp = addSpinner(p.name,p.min,p.max,i,value[i],enabled);
			if(!p.toolTip.isNull()){
				(dynamic_cast<QSpinBox*>(temp))->setSuffix(p.toolTip);
			}
		}
		else if (p.type == "Slider"){
			temp = 	addSlider(p.name,p.min,p.max,i,value[i],enabled);
			
		}
		else if(p.type == "Entry"){

		}
		else if(p.type == "Text"){

		}
		temp->setToolTip(p.toolTip);
		listPropriete.append(temp);
		i++;
	}
	
	addApplyButton(i);
}

void FilterWindow::addApplyButton(int row){
	QPushButton *push = new QPushButton("Appliquer",proprieteSection);
	QObject::connect(push,SIGNAL(clicked()),this,SLOT(applyFilterOrTool()));
	layout->addWidget(push,row,2);
}

void FilterWindow::applyFilterOrTool(){
	
	if(proprieteFilterActual=="filtreLineaire"){
		applyFiltreLineaire();
	}
	else if(proprieteFilterActual=="filtreNonLineaire"){
		applyFiltreNonLineaire();
	}
	else if(proprieteFilterActual=="resize pixel"){
		applyResizePixel();
	}
	else if(proprieteFilterActual=="resize scale"){
		applyResizeScale();
	}
	else if(proprieteFilterActual == "crop"){
		applyCrop();
	}
	else if(proprieteFilterActual == "segmentationCouleur"){
		applySegmentationCouleur();
	}
	else if(proprieteFilterActual == "segmentationMonochrome"){
		applySegmentationMono();
	}
	else if(proprieteFilterActual == "ConvolutionUni"){
		applyConvolution();
	}
}

void FilterWindow::applySegmentationCouleur(void){
	QVector<int> listFactor(3);
	int k=0;

	Q_FOREACH(QWidget *w, listPropriete){
		listFactor[k] = (dynamic_cast<QSlider*>(w))->value();
		k++;
	}
	eraseProperties();
	dynamic_cast<MainWindow*>(this->parent())->applySegmentationCouleur(listFactor);
}
void FilterWindow::applySegmentationMono(void){
	int facteur;

	facteur = dynamic_cast<QSlider*>(listPropriete[0])->value();
	eraseProperties();
	dynamic_cast<MainWindow*>(this->parent())->applySegmentationMono(facteur);
}
void FilterWindow::applyFiltreLineaire(void){
	QVector<float> listFactor(12);
	int k=0;

	Q_FOREACH(QWidget *w, listPropriete){
		listFactor[k] = static_cast<float>((dynamic_cast<QDoubleSpinBox*>(w))->value());
		k++;
	}
	eraseProperties();
	dynamic_cast<MainWindow*>(this->parent())->applyFiltreLineaire(listFactor);
}
void FilterWindow::applyFiltreNonLineaire(void){
	QVector<float> listFactor(3);
	int k=0;

	Q_FOREACH(QWidget *w, listPropriete){
		listFactor[k] = static_cast<float>((dynamic_cast<QDoubleSpinBox*>(w))->value());
		k++;
	}
	eraseProperties();
	dynamic_cast<MainWindow*>(this->parent())->applyFiltreNonLineaire(listFactor);
}
void FilterWindow::applyResizeScale(void){
	QVector<float> listFactor(2);
	int k=0;

	Q_FOREACH(QWidget *w, listPropriete){
		listFactor[k] = static_cast<float>((dynamic_cast<QDoubleSpinBox*>(w))->value());
		k++;
	}
	eraseProperties();
	dynamic_cast<MainWindow*>(this->parent())->applyResizeScale(listFactor[0],listFactor[1]);
}
void FilterWindow::applyResizePixel(void){
	QVector<int> listFactor(2);
	int k=0;

	Q_FOREACH(QWidget *w, listPropriete){
		listFactor[k] = (dynamic_cast<QSpinBox*>(w))->value();
		k++;
	}
	eraseProperties();
	dynamic_cast<MainWindow*>(this->parent())->applyResizePixel(listFactor[0],listFactor[1]);
}
void FilterWindow::applyCrop(void){
	QVector<int> listFactor(4);
	int k=0;

	Q_FOREACH(QWidget *w, listPropriete){
		listFactor[k] = (dynamic_cast<QSpinBox*>(w))->value();
		k++;
	}
	eraseProperties();
	dynamic_cast<MainWindow*>(this->parent())->applyCrop(listFactor[0],listFactor[1],listFactor[2],listFactor[3]);
}

void FilterWindow::applyConvolution(void){
	int facteur;

	facteur = dynamic_cast<QSlider*>(listPropriete[0])->value();
	eraseProperties();
	dynamic_cast<MainWindow*>(this->parent())->applyConvolution(facteur);
}

void FilterWindow::eraseProperties(){
	while(layout->count() > 0) {
        QWidget* widget = layout->itemAt(0)->widget();
        layout->removeWidget(widget);
        delete widget;
    }
	listPropriete.clear();
}