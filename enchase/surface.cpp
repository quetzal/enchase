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

	void Surface::process(MatrixF* matrix, ccglobal::Tracer* tracer)
	{
		edgeProcess(matrix, edgeType);
		if (tracer != nullptr)
		{
			tracer->progress(0.2f);
		}

		if (invert)
		{
			printf("invert\n");
			*matrix = 1 - *matrix;
		}
		if (tracer != nullptr)
		{
			tracer->progress(0.3f);
		}

		if (useBlur > 0)
		{
			blur(matrix, useBlur, tracer);
		}

		if (convertType == 1)
		{
			transparencyConvert(matrix, baseHeight, maxHeight, 25);
		}
		else
		{
			normalConvert(matrix, baseHeight, maxHeight);
		}
		if (tracer != nullptr)
		{
			tracer->progress(0.9f);
		}
	}

	void Surface::process(MatrixF* matrix)
	{
		edgeProcess(matrix, edgeType);

		if (invert)
		{
			printf("invert\n");
			*matrix = 1 - *matrix;
		}

		if (useBlur)
		{
			blur(matrix, blurTimes);
		}

		if (convertType == 1)
		{
			transparencyConvert(matrix, baseHeight, maxHeight, 25);
		}
		else
		{
			normalConvert(matrix, baseHeight, maxHeight);
		}
	}

	MatrixF* Surface::matrix()
	{
		MatrixF* m = produce();
		if (m) process(m);
		return m;
	}

	MatrixF* Surface::matrix(ccglobal::Tracer* tracer)
	{
		MatrixF* m = produce();
		if (tracer != nullptr)
		{
			tracer->progress(0.1f);
		}
		if(m) process(m, tracer);
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