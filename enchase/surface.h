#ifndef ENCHASE_SURFACE_1601262551755_H
#define ENCHASE_SURFACE_1601262551755_H
#include <memory>
#include <string>
#include "imagematrix.h"
#include "enum.h"
#include "ccglobal/tracer.h"

namespace enchase
{
	class Surface
	{
	public:
		Surface();
		virtual ~Surface();

		MatrixF* matrix(ccglobal::Tracer* tracer);
		MatrixF* matrix();

		virtual MatrixF* produce() = 0;
		void setIndex(int index);
		int index();
	protected:
		void process(MatrixF* matrix);
		void process(MatrixF* matrix, ccglobal::Tracer* tracer);
	public:
		int convertType;
		float baseHeight;
		float maxHeight;

		int useBlur;
		bool invert;
		EdgeType edgeType;

		int useIndex;
		int blurTimes;
		int colorSegment;
	};

	typedef std::shared_ptr<Surface> SurfacePtr;
}

#endif // ENCHASE_SURFACE_1601262551755_H