#include "SegmentationCouleur.h"

SegmentationCouleur::SegmentationCouleur(QVector<int> seuil){
	SegmentationCouleur::seuil = seuil;
}
QList<Modifier::proprieteGenerique> SegmentationCouleur::feedProperties(void){
	QList<Modifier::proprieteGenerique> propriete;
	proprieteGenerique p;

	p.max=255;
	p.min=0;
	p.type="Slider";
	
	for(int f=0;f<3;f++){
		switch(f){
			case 0:
				p.name="Seuil rouge";
				break;
			case 1:
				p.name="Seuil vert";
				break;
			case 2:
				p.name="Seuil bleu";
				break;
		}
		p.toolTip = "valeur entre 0 et 255";
		propriete.append(p);
	}


	return propriete;
}
QImage SegmentationCouleur::execute(QImage image,QVector<int> seuil){
	register unsigned char *i;
	
	i = image.bits();

	register unsigned char *last = i + image.width()*image.height()*4;

	while(i<last){
		if(*i <= seuil[0]){
			*i++=0;
		}
		else{
			*i++=255;
		}
		
		if(*i <= seuil[1]){
			*i++=0;
		}
		else{
			*i++=255;
		}
		
		if(*i <= seuil[2]){
			*i++=0;
		}
		else{
			*i++=255;
		}
		*i++;
	}

	return image;
}
QVector<float> SegmentationCouleur::getDefaultValue(void){
	QVector<float> value;
	value <<175 << 175 << 175;
	return value;
}