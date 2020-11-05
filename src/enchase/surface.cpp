#include "surface.h"
#include "blur.h"
#include "heightconvert.h"
#include "edgeprocessor.h"

namespace enchase
{
	Surface::Surface()
		: useBlur(0)
		, convertType(0)
		, baseHeight(0.35f)
		, maxHeight(2.2f)
		, invert(true)
		, useIndex(0)
		, edgeType(EdgeType::et_none)
		, colorSegment(0)
	{

	}

	Surface::~Surface()
	{

	}

	void Surface::process(MatrixF* matrix, qtuser_core::Progressor* progressor)
	{
		edgeProcess(matrix, edgeType);
		if (progressor != nullptr)
		{
			progressor->progress(0.2f);
		}

		if (invert)
		{
			printf("invert\n");
			*matrix = 1 - *matrix;
		}
		if (progressor != nullptr)
		{
			progressor->progress(0.3f);
		}

		if (useBlur > 0)
		{
			blur(matrix, useBlur, progressor);
		}

		if (convertType == 1)
		{
			transparencyConvert(matrix, baseHeight, maxHeight, 25);
		}
		else
		{
			normalConvert(matrix, baseHeight, maxHeight);
		}
		if (progressor != nullptr)
		{
			progressor->progress(0.9f);
		}
	}

	MatrixF* Surface::matrix(qtuser_core::Progressor* progressor)
	{
		MatrixF* m = produce();
		if (progressor != nullptr)
		{
			progressor->progress(0.1f);
		}
		if(m) process(m, progressor);
		return m;
	}

	void Surface::setIndex(int index)
	{
		useIndex = index;
	}

	int Surface::index()
	{
		return useIndex;
	}
}