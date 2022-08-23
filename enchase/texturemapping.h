#ifndef ENCHASE_TEXTUREMAPPING_1621324751120_H
#define ENCHASE_TEXTUREMAPPING_1621324751120_H
#include <string>

namespace trimesh
{
	class TriMesh;
}

namespace enchase
{
	class Surface;
	class TextureMappingParam
	{
	public:
		TextureMappingParam();
		~TextureMappingParam();

		float baseThickness;
		float maxThickness;

		bool useBlur;
		int blurTimes;

		bool invert;

		float radius;
		float shellThickness;
		float clipHeight;

		bool onlyCreateOutter;
	};

	class TextureMapping
	{
	public:
		TextureMapping();
		~TextureMapping();

		void setSource(const std::string& imageName);   //现在支持bmp, png, jpg
		void setSource(const std::string& extension, int fd);
		void setSource(unsigned char* data, int width, int height);   //灰度值

		bool generate(const std::string& stlFile, const TextureMappingParam& param);
		trimesh::TriMesh* generate(const TextureMappingParam& param);
	protected:
		enchase::Surface* m_surface;
	};
}

#endif // ENCHASE_TEXTUREMAPPING_1621324751120_H