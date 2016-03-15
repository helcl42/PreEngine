#ifndef IMD2_MODEL_FACTORY_H
#define IMD2_MODEL_FACTORY_H

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace MD2
			{
				class IMD2ModelFactory
				{
				public:
					virtual MD2Model* CreateModel(const std::string& filePath) = 0;

				public:
					virtual ~IMD2ModelFactory() {}
				};
			}
		}
	}
}

#endif