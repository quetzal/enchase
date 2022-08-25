#include "trimeshgenerator.h"
#include "mapper.h"
#include "enchaser.h"
#include "texturegroup.h"
#include "imagematrixfsource.h"
//#include "mmesh/trimesh/trimeshutil.h"

namespace enchase
{
	trimesh::TriMesh* enchaseGenerate(trimesh::TriMesh* input, SurfacePtr surface)
	{
		if (!input || input->cornerareas.size() == 0)
			return nullptr;

		MatrixF* mat = surface->matrix();
		if (!surface || !mat)
			return nullptr;

		//if(ball && (float)mat->width()/(float)mat->height() > 1.5f)
		//	mmesh::convertUV2Equ(input);   /////////$$$$$$$$$$$$$$$$$$$$$$$$/////////////////////////

		enchase::Mapper mapper;
		enchase::Enchaser enchaser;
		enchaser.setSource(input);

		enchase::TextureGroup* texture = new enchase::TextureGroup();
		size_t size = input->vertices.size();
		if (size > 0)
		{
			texture->m_indexes.resize(size);
			texture->m_texcoord.resize(size);

			for (size_t i = 0; i < size; ++i)
			{
				texture->m_indexes.at(i) = (int)i;
				texture->m_texcoord.at(i) = input->cornerareas.at(i);
			}
		}

		mapper.allTextureGroup().push_back(texture);

		mapper.setSource(new enchase::MatrixFSource(mat));
		enchaser.enchaseCache(&mapper, 0);

		trimesh::TriMesh* mesh = enchaser.takeCurrent();
		if (mesh)
			mesh->cornerareas.clear();

		return mesh;
	}

	void mappingTriMesh(trimesh::TriMesh* input, int type)
	{
		if (!input)
			return;

		int vertexSize = (int)input->vertices.size();
		if (vertexSize <= 0)
			return;

		input->need_normals();
		input->need_bbox();

		input->cornerareas.resize(vertexSize);

		typedef std::function<trimesh::point(const trimesh::vec3& pos)> uvFunc;
		uvFunc funcs[3];
		uvFunc cubeFunc = [](const trimesh::vec3& pos)->trimesh::point {
			return (trimesh::vec3(1.0f, 1.0f, 0.0f) + pos) / 2.0f;
		};
		uvFunc sphereFunc = [](const trimesh::vec3& pos)->trimesh::point {
			float r = trimesh::len(pos);
			float V = acos(pos.z / r) / M_PIf;
			float d = pos.x / r / sin(M_PIf * V);

			if (d > 1.0f)
				d = 1.0f;
			if (d < -1.0f)
				d = -1.0f;

			float U = acos(d) / M_PIf / 2.0f;

			return trimesh::vec3(U, V, 0.0f);
		};
		uvFunc cylinderFunc = [](const trimesh::vec3& pos)->trimesh::point {
			return trimesh::vec3(0.0f, 0.0f, 0.0f);
		};
		funcs[0] = cubeFunc;
		funcs[1] = sphereFunc;
		funcs[2] = cylinderFunc;

		if (type < 0)
			type = 0;
		if (type > 2)
			type = 2;

		trimesh::box3 box = input->bbox;
		trimesh::vec3 boxSize = box.max - box.min;
		trimesh::vec3 boxCenter = (box.max + box.min) / 2.0f;
		float r = std::max(boxSize.z, std::max(boxSize.x, boxSize.y)) / 2.0f;

		for (int i = 0; i < vertexSize; ++i)
		{
			if (i == 22147)
				int j = 0;

			trimesh::vec3 pos = input->vertices.at(i);
			pos = (pos - boxCenter) / r;
			input->cornerareas.at(i) = funcs[type](pos);
		}
	}
}