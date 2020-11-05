#ifndef ENCHASE_BLUR_1600480088460_H
#define ENCHASE_BLUR_1600480088460_H
#include "imagematrix.h"
#include "qtusercore/module/progressor.h"

namespace enchase
{
	void blur(MatrixF* matrix, int blurNum, qtuser_core::Progressor* progressor);
}

#endif // ENCHASE_BLUR_1600480088460_H