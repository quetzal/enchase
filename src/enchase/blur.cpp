#include "blur.h"

namespace enchase
{
	void blur(MatrixF* matrix, int blurNum, qtuser_core::Progressor* progressor)
	{
		MatrixF f(3, 3, 1, 1.0 / 9.0);
		MatrixF* matrix2 = new MatrixF(*matrix);

		int i = 0;
		for (i = 0; i + 1 < blurNum; i += 2)
		{
			matrix->conv(f, MatrixF::PAD_EDGE, *matrix2);
			matrix2->conv(f, MatrixF::PAD_EDGE, *matrix);

			if (progressor != nullptr)
			{
				progressor->progress(0.3f + 0.5f / blurNum * (i+1));
			}
		}
		if (i < blurNum)
		{
			matrix->conv(f, MatrixF::PAD_EDGE, *matrix2);
			*matrix = *matrix2;

			if (progressor != nullptr)
			{
				progressor->progress(0.3f + 0.5f / blurNum * (i + 1));
			}
		}

		delete matrix2;
	}
}