#ifndef ANIMATION_TYPE_H
#define ANIMATION_TYPE_H

#include "../../../Core/Common.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace MD2
			{
				enum AnimationType
				{
					STAND,
					RUN,
					ATTACK,
					PAIN_A,
					PAIN_B,
					PAIN_C,
					JUMP,
					FLIP,
					SALUTE,
					FALLBACK,
					WAVE,
					POINT,
					CROUCH_STAND,
					CROUCH_WALK,
					CROUCH_ATTACK,
					CROUCH_PAIN,
					CROUCH_DEATH,
					DEATH_FALLBACK,
					DEATH_FALLFORWARD,
					DEATH_FALLBACKSLOW,
					BOOM,

					MAX_ANIMATIONS

				};

				std::string GetAnimationTypeName(AnimationType animationType);
			}
		}
	}
}

#endif