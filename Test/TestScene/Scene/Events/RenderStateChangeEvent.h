#ifndef MATRICES_MESSAGE_H
#define MATRICES_MESSAGE_H

#include <PreEngine/Core/Common.h>
#include <PreEngine/Core/Events/BaseEvent.h>
#include <PreEngine/Render/Lightning/Material.h>

#include "RenderPassType.h"

namespace TestScene
{
	namespace Events
	{
		using namespace PreEngine::Render::Lightning;
		using namespace PreEngine::Core::Events;

		struct RenderStateChangeEvent : public BaseEvent
		{
			RenderPassType renderPassType;

			glm::mat4 projectionMatrix;

			glm::mat4 viewMatrix;

			glm::mat4 lightProjectionViewMatrix;

			bool useBumpMaps;

			bool showNormals;

			float normalLength;

			Material shinyMaterial;

			RenderStateChangeEvent(RenderPassType passType, glm::mat4 projection, glm::mat4 view, glm::mat4 lpm, bool useBumpMaps, bool showNormals, float normalLength, Material shinyMaterial)
				: renderPassType(passType), projectionMatrix(projection), viewMatrix(view), lightProjectionViewMatrix(lpm), useBumpMaps(useBumpMaps), showNormals(showNormals), normalLength(normalLength), shinyMaterial(shinyMaterial)
			{
			}

			virtual ~RenderStateChangeEvent()
			{
			}
		};
	}
}

#endif