#include "texturemapping.h"

#include "mapper.h"
#include "enchaser.h"
#include "imagematrixfsource.h"
#include "surface.h"
#include "datasurface.h"
#include "imageloader.h"

#include "trimeshgenerator.h"
//#include "mmesh/trimesh/trimeshutil.h"
//#include "mmesh/trimesh/split.h"
//#include "mmesh/create/ballcreator.h"

#include "trimesh2/TriMesh_algo.h"
#include <memory>

namespace enchase
{
	TextureMappingParam::TextureMappingParam()
	{
		useBlur = true;
		blurTimes = 9;

		baseThickness = 0.35f;
		maxThickness = 2.2f;
		invert = false;

		radius = 10.0f;
		shellThickness = 1.0f;
		clipHeight = 4.0f;
        onlyCreateOutter = false;
	}

	TextureMappingParam::~TextureMappingParam()
	{

	}

	TextureMapping::TextureMapping()
		:m_surface(nullptr)
	{
	}

	TextureMapping::~TextureMapping()
	{
		if (m_surface)
		{
			delete m_surface;
			m_surface = nullptr;
		}
	}

	void TextureMapping::setSource(const std::string& extension, int fd)
	{
		enchase::ImageData image;

		enchase::loadImage_freeImage(image, extension, fd);

		if (image.width == 0 || image.height == 0 || image.data == nullptr)
			return;

		setSource(image.data, image.width, image.height);
		if (image.data)
		{
			delete[] image.data;
		}
	}

	void TextureMapping::setSource(const std::string& imageName)
	{
		enchase::ImageData image;

		enchase::loadImage_freeImage(image, imageName);

		if (image.width == 0 || image.height == 0 || image.data == nullptr)
			return;

		setSource(image.data, image.width, image.height);
		if (image.data)
		{
			delete[] image.data;
		}
	}

	void TextureMapping::setSource(unsigned char* data, int width, int height)
	{
		if (m_surface)
		{
			delete m_surface;
			m_surface = nullptr;
		}

		enchase::DataSurface* surface = new enchase::DataSurface();
		surface->setData(data, width, height);
		m_surface = surface;
	}

	bool TextureMapping::generate(const std::string& stlFile, const TextureMappingParam& param)
	{
		std::unique_ptr<trimesh::TriMesh> destPtr(generate(param));
		if (destPtr)
		{
			destPtr->write(stlFile);
			return true;
		}

		return false;
	}

	trimesh::TriMesh* TextureMapping::generate(const TextureMappingParam& param)
	{
		if (!m_surface)
			return nullptr;

		m_surface->baseHeight = param.baseThickness;
		m_surface->maxHeight = param.maxThickness;
		m_surface->invert = param.invert;
		m_surface->useBlur = param.useBlur;
		m_surface->blurTimes = param.blurTimes;

		//trimesh::TriMesh* mesh = mmesh::BallCreator::create(param.radius + param.shellThickness, 8, 2);
		trimesh::TriMesh* mesh = new trimesh::TriMesh();
		size_t size = mesh->vertices.size();
		if (mesh->normals.size() != size && size > 0)
		{
			mesh->normals.resize(size);
			for (size_t i = 0; i < size; ++i)
				mesh->normals.at(i) = trimesh::normalized(mesh->vertices.at(i));
		}

		trimesh::TriMesh* meshOut = enchaseGenerate(mesh, SurfacePtr(m_surface), true);
		
		return meshOut;
	}
}