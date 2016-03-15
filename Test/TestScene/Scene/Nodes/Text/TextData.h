#ifndef TEXT_DATA_H
#define TEXT_DATA_H

#include <PreEngine/Core/Common.h>

namespace TestScene
{
	namespace Nodes
	{
		struct TextData
		{
			std::string message;

			unsigned int positionX;

			unsigned int positionY;

			unsigned int size;

			glm::vec4 color;


			TextData();

			TextData(const std::string& message, unsigned int x, unsigned int y, unsigned int size, glm::vec4 color);

			virtual ~TextData();
		};
	}
}

#endif