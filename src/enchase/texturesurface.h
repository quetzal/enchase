#ifndef ENCHASE_TEXTURESURFACE_1601262551775_H
#define ENCHASE_TEXTURESURFACE_1601262551775_H

#include "surface.h"
#include <QString>

namespace enchase
{
	class TextureSurface : public Surface
	{
	public:
		TextureSurface();
		virtual ~TextureSurface();

		void setTextureFile(QString& file);
	protected:
		MatrixF* produce() override;

	protected:
		QString m_file;
	};
}

#endif // ENCHASE_TEXTURESURFACE_1601262551775_H