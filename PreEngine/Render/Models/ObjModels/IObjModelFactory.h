#ifndef IOBJ_MODEL_FACTORY_H
#define IOBJ_MODEL_FACTORY_H

#include "../../../Core/Common.h"
#include "../IModel.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace ObjModels
			{
				class IObjModelFactory
				{
				public:
					virtual IModel* CreateModel(const std::string& filePath, const std::string& mtlFilePath) = 0;

				public:
					virtual ~IObjModelFactory() {}
				};
			}
		}
	}
}

#endif