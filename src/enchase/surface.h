#ifndef ENCHASE_SURFACE_1601262551755_H
#define ENCHASE_SURFACE_1601262551755_H
#include <memory>
#include <string>
#include "imagematrix.h"
#include "enum.h"
#include "qtusercore/module/progressor.h"

namespace enchase
{
	class Surface
	{
	public:
		Surface();
		virtual ~Surface();

		MatrixF* matrix(qtuser_core::Progressor* progressor);
		virtual MatrixF* produce() = 0;
		void setIndex(int index);
		int index();
	protected:
		void process(MatrixF* matrix, qtuser_core::Progressor* progressor);
	public:
		int convertType;
		float baseHeight;
		float maxHeight;

		int useBlur;
		bool invert;
		EdgeType edgeType;

		int useIndex;

		int colorSegment;
	};

	typedef std::shared_ptr<Surface> SurfacePtr;
}

#endif // ENCHASE_SURFACE_1601262551755_H