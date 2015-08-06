#include "Convolution.h"

Convolution::Convolution(int facteur,QString type):Modifier(){
	Convolution::facteur = facteur;
	Convolution::type= type;
}

QList<Modifier::proprieteGenerique> Convolution::feedProperties(void){
	QList<Modifier::proprieteGenerique> p;

	proprieteGenerique propri;
	propri.type = "Slider";
	propri.name = "dimension";
	propri.max = 99;
	propri.min = 3;
	propri.toolTip = "Nombre impaires seulement";

	p.append(propri);

	return p;
}


QImage Convolution::execute(QImage image,int dimension,QString type){
	float *facteur = generateFactorGrid(dimension,type);

	int width = image.width();
	int height = image.height();

	QImage iOutput =  image;
	unsigned char *pSource = image.bits();
	unsigned char *pTarget = iOutput.bits();
	
	unsigned char *iR = new unsigned char[width*height];
	unsigned char *iG = new unsigned char[width*height];
	unsigned char *iB = new unsigned char[width*height];
	unsigned char *oR = new unsigned char[width*height];
	unsigned char *oG = new unsigned char[width*height];
	unsigned char *oB = new unsigned char[width*height];
	unsigned char *pR, *pG, *pB, *qR, *qG, *qB;

	if(!iR || !iG || !iB|| !oR || !oG || !oB || !facteur){
		return image;
	}

	pR = iR; pG = iG; pB = iB; 
	qR = oR; qG = oG; qB = oB; 

	while (pSource < image.bits() + width*height*4){
		*pR++ = *pSource++;			
		*pG++ = *pSource++;			
		*pB++ = *pSource++;
		pSource++;
		*qR++ = *pTarget++;			
		*qG++ = *pTarget++;			
		*qB++ = *pTarget++;
		pTarget++;
	}

	float newValR = 0.0f;
	float newValG = 0.0f;
	float newValB = 0.0f;
	int padding = (dimension-1)/2;
	int offset,offsetFacteur;

	for(int h = padding; h < height - padding+1; h++){
		for(int w = padding; w < width - padding+1; w++){
			newValR = 0.0f;
			newValG = 0.0f;
			newValB = 0.0f;
			int i = 0;
			for(int p = h-padding; p < h+padding; p++,i++) {
				int j = 0;
				for(int q = w-padding; q< w+padding; q++,j++) {
					offset = p*width + q; 
					offsetFacteur = i*dimension + j;
					newValR += iR[offset] * facteur[offsetFacteur];
					newValG += iG[offset] * facteur[offsetFacteur];
					newValB += iB[offset] * facteur[offsetFacteur];
				}
			}
			offset = h*width + w;
			oR[offset] = static_cast<unsigned char>(newValR);
			oG[offset] = static_cast<unsigned char>(newValG);
			oB[offset] = static_cast<unsigned char>(newValB);
		}
	}

	pSource = image.bits();
	for(int y = 0; y < height; y++){
		for(int x = 0; x < width; x++){
			if(x<padding || y<padding){
				*pSource++ = 0;
				*pSource++ = 0;
				*pSource++ = 0;
			}
			else if(x>width-padding || y>height-padding){
				*pSource++ = 0;
				*pSource++ = 0;
				*pSource++ = 0;
			}
			else{
				offset = y*width + x;
				*pSource++ = oR[offset];
				*pSource++ = oG[offset];
				*pSource++ = oB[offset];
			}
			pSource++;
		}
	}

	delete[] iR;
	delete[] iG;
	delete[] iB;
	delete[] oR;
	delete[] oG;
	delete[] oB;
	delete[] facteur;

	return image;
}

QVector<float> Convolution::getDefaultValue(){
	QVector<float> value;
	value << 9.0;
	return value;
}
float* Convolution::generateFactorGrid(int dimension,QString type){
	float *facteur = new float[dimension*dimension];
	
	float *f = facteur,*pf=facteur+dimension*dimension;


	for (int i = 0; i < dimension; i++) {
		for(int k =0 ;k < dimension;k++){
			*f=0.0f;
			
			if(type == "U"){
				*f= 1.0f /(dimension*dimension);
			}
			else if(type == "G"){

			}
			else if(type == "N"){
				if(k == (dimension/2) && i <= (dimension/2)){
					*f=1.0f;
				}
			}
			else if(type == "S"){
				if(k == (dimension/2) && i >= (dimension/2)){
					*f=1.0f;
				}
			}
			else if(type == "W"){
				if(i == (dimension/2) && k <= (dimension/2)){
					*f=1.0f;
				}
			}
			else if(type == "E"){
				if(i == (dimension/2) && k >= (dimension/2)){
					*f=1.0f;
				}
			}
			else if(type == "NW"){
				if(i <= (dimension/2) && k <=(dimension/2) && i==k){
					*f=1.0f;
				}
			}
			else if(type == "NE"){
				if(i <= (dimension/2) && k >=(dimension/2) && i+k == dimension-1){
					*f=1.0f;
				}
			}
			else if(type == "SW"){
				if(i >= (dimension/2) && k <=(dimension/2) && i+k == dimension-1){
					*f=1.0f;
				}				
			}
			else if(type == "SE"){
				if(i >= (dimension/2) && k >=(dimension/2) && i==k){
					*f=1.0f;
				}
			}

			*f++;
		}

	}

	return facteur;
}