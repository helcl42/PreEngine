#include "TextData.h"

namespace TestScene
{
	namespace Nodes
	{
		TextData::TextData()
		{
		}

		TextData::TextData(const std::string& message, unsigned int x, unsigned int y, unsigned int size, glm::vec4 color)
			: message(message), positionX(x), positionY(y), size(size), color(color)
		{
		}

		TextData::~TextData()
		{
		}
	}
}