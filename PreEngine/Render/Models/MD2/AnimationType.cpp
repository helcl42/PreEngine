#include "AnimationType.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace MD2
			{
				std::string GetAnimationTypeName(AnimationType animationType)
				{
					switch (animationType)
					{
					case AnimationType::STAND:
						return "Stand";
					case AnimationType::RUN:
						 return "Run";
					case AnimationType::ATTACK:
						return "Attack";
					case AnimationType::PAIN_A:
						return "Pain A";
					case AnimationType::PAIN_B:
						return "Pain B";
					case AnimationType::PAIN_C:
						return "Pain C";
					case AnimationType::JUMP:
						return "Jump";
					case AnimationType::FLIP:
						return "Flip";
					case AnimationType::SALUTE:
						return "Salute";
					case AnimationType::FALLBACK:
						return "Fallback";
					case AnimationType::WAVE:
						return "Wave";
					case AnimationType::POINT:
						return "Point";
					case AnimationType::CROUCH_STAND:
						return "Crouch Stand";
					case AnimationType::CROUCH_WALK:
						return "Crouch Walk";
					case AnimationType::CROUCH_ATTACK:
						return "Crouch Attack";
					case AnimationType::CROUCH_PAIN:
						return "Crouch Pain";
					case AnimationType::CROUCH_DEATH:
						return "Crouch Death";
					case AnimationType::DEATH_FALLBACK:
						return "Death Fallback";
					case AnimationType::DEATH_FALLFORWARD:
						return "Death Fall Forward";
					case AnimationType::DEATH_FALLBACKSLOW:
						return "Death Fallback Slow";
					case AnimationType::BOOM:
						return "Boom";
					default:
						return "UNKNOWN";
					}
				}
			}
		}
	}
}
