#ifndef TOOLS_H
#define TOOLS_H

#include "Modifier.h"

class Rotation: public Modifier{
	public:
		Rotation(int nbRotation);
		static QImage execute(QImage img ,int nbRotation);

		int nbRotation;
};

class Miroir: public Modifier{
	public:
		Miroir(char direction);
		static QImage execute(QImage img,char direction);
		
		char direction;
};

class ResizeScale: public Modifier{
	public:
		ResizeScale(float xRatio, float yRatio);
		
		static QImage execute(QImage img, float xRatio, float yRatio);
		static QList<Modifier::proprieteGenerique> feedResizeScaleProperties();
		static QVector<float> getDefaultValueResizeScale(void);

		float xRatio;
		float yRatio;
};

class ResizePixel: public Modifier{
	public:
		ResizePixel(float xPixel, float yPixel);

		static QImage execute(QImage img, float xPixel, float yPixel);
		static QList<Modifier::proprieteGenerique> feedResizePixelProperties();

		 float xPixel; 
		 float yPixel;
};

class Crop: public Modifier{
	public:
		Crop(int startX, int startY,int endX, int endY);
		static QImage execute(QImage img,int startX, int startY,int endX, int endY);
		static QList<Modifier::proprieteGenerique> feedCropProperties(int width, int height);

		int startX;
		int startY;
		int endX; 
		int endY;
};

class Tools{
	public:
		Tools();
		QList<QString> getListOrdreTools();
	private:
		QList<QString> listOrdreTools;
};

#endif