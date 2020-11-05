#ifndef ENCHASE_LOADER_1600318223169_H
#define ENCHASE_LOADER_1600318223169_H
#include "trimesh2/Vec.h"
#include "ImageMatrix.h"
#include <vector>
#include <QString>

namespace trimesh
{
	class TriMesh;
}

class QImage;
namespace enchase
{
	
	MatrixF* loadImage(QString file, int segment = 0);
	MatrixF* loadFromImage(QImage* image, int segment = 0);
}

#endif // ENCHASE_LOADER_1600318223169_H