#include "loader.h"
#include "trimesh2/TriMesh.h"
#include "texturegroup.h"

#include <QtGui/QImage>
#include <fstream>

namespace enchase
{
	
	MatrixF* loadImage(QString file, int segment)
	{
		QImage image(file);
		return loadFromImage(&image, segment);
	}

	MatrixF* loadFromImage(QImage* image, int segment)
	{
		uint width = (uint)image->width();
		uint height = (uint)image->height();
		if (width == 0 || height == 0)
		{
			printf("load image error\n");
			return nullptr;
		}

		MatrixF* imgMtx = new MatrixF(width, height, 1);
		float* imgData = imgMtx->ptr(0);

		for (int h = 0; h < height; h++)
		{
			for (int w = 0; w < width; w++)
			{
				QRgb qrgb = image->pixel(w, h);
				{
					//imgData[w] = (0.212655 * qRed(qrgb) + 0.715158 * qGreen(qrgb) + 0.072187 * qBlue(qrgb)) / 255.0;
				}

				unsigned char gray = qGray(qrgb);
				if (segment > 0)
				{
					gray = (gray / segment) * segment;
				}
				
				imgData[w] = (float)gray / 255.0f;
			}
			imgData = imgMtx->ptr(h);
		}
		return imgMtx;
	}
}