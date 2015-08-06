#include "SegmentationMono.h"

SegmentationMono::SegmentationMono(int seuil){
	SegmentationMono::seuil = seuil;
}
QList<Modifier::proprieteGenerique> SegmentationMono::feedProperties(void){
	
	QList<Modifier::proprieteGenerique> propriete;
	proprieteGenerique pro;
	
	pro.max=255;
	pro.min=0;
	pro.name="Seuil";
	pro.type="Slider";
	pro.toolTip = "valeur entre 0 et 255";

	propriete.append(pro);

	return propriete;
}
QImage SegmentationMono::execute(QImage image,int seuil){
	register unsigned char *i;
	register unsigned int *im;
	i = image.bits();

	register unsigned char *last = i + image.width()*image.height()*4;

	int pixel;
	while(i<last){
		pixel = 0;
		
		pixel += *i++;
		pixel += *i++;
		pixel += *i;
		*i--;*i--;
		
		pixel/=3;
		if(pixel<=seuil){
			*i++=0;
			*i++=0;
			*i++=0;
		}
		else{
			*i++=255;
			*i++=255;
			*i++=255;
		}

		*i++;
	}

	return image;
}

QVector<float> SegmentationMono::getDefaultValue(void){
	QVector<float> value;
	value << 175.0;
	return value;
}