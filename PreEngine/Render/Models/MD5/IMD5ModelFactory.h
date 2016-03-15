#ifndef IMD5MODEL_FACTORY_H
#define IMD5MODEL_FACTORY_H

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace MD5
			{
				class IMD5ModelFactory
				{
				public:
					virtual MD5Model* CreateModel(const std::string& filePath) = 0;

				public:
					virtual ~IMD5ModelFactory() {}
				};
			}
		}
	}
}

#endif