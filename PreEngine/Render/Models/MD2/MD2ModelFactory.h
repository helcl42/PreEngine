#ifndef MD2_MODEL_FACTORY_H
#define MD2_MODEL_FACTORY_H

#include "../../../Core/Common.h"
#include "../AbstractModelFactory.h"

#include "MD2ModelCommon.h"
#include "MD2Model.h"
#include "IMD2ModelFactory.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace MD2
			{
				class MD2ModelFactory : public AbstractModelFactory, public IMD2ModelFactory
				{
				private:
					AnimationHeader m_header;

					std::vector<std::vector<glm::vec3>> m_vertices;

					std::vector<std::vector<int>> m_normals;

					std::vector<int> m_commands;

				public:
					MD2ModelFactory();

					virtual ~MD2ModelFactory();

				private:
					void PrepareModelStructures(MD2Model* model);

					void ReadCommands(FILE* file);

					void ReadFramesData(FILE* file);

					void ReadCommandData(MD2Model* model);

					void BindData(MD2Model* model);

					void SetTexture(MD2Model* model, std::string filePath);

				public:
					MD2Model* CreateModel(const std::string& filePath);
				};
			}
		}
	}
}

#endif