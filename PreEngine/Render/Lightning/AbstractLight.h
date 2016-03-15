#ifndef ABSTRACT_LIGHT_H
#define ABSTRACT_LIGHT_H

#include "../../Core/Common.h"
#include "ILight.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Lightning
		{
			class AbstractLight : public ILight
			{
			protected:
				glm::vec3 m_color;

			public:
				AbstractLight(glm::vec3 color);

				virtual ~AbstractLight();

			public:
				void SetColor(glm::vec3 color);

				glm::vec3 GetColor() const;
			};
		}
	}
}

#endif