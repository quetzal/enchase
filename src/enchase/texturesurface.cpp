#include "texturesurface.h"
#include "loader.h"

namespace enchase
{
	TextureSurface::TextureSurface()
	{

	}

	TextureSurface::~TextureSurface()
	{

	}

	void TextureSurface::setTextureFile(QString& file)
	{
		m_file = file;
	}

	MatrixF* TextureSurface::produce()
	{
		return loadImage(m_file);
	}
}