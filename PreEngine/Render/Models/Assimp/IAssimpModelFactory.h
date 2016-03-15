#ifndef IASSIMP_MODEL_FACTORY_H
#define IASSIMP_MODEL_FACTORY_H

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace Assimp
			{
				class IAssimpModelFactory
				{
				public:
					virtual IModel* CreateModel(std::string filePath) = 0;

					virtual IModel* CreateModel(std::string filePath, std::string texturePath) = 0;

					virtual IModel* CreateModel(std::string filePath, std::string texturePath, std::string normalTexturePath) = 0;

				public:
					virtual ~IAssimpModelFactory() {}
				};
			}
		}
	}
}

#endif