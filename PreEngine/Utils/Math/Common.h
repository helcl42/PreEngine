#include "../../Core/Common.h"

namespace PreEngine
{
	namespace Utils
	{
		namespace Math
		{
			class MathUtils
			{
			public:
				template <class T>
				static inline T ComputeQuaternionW(const glm::quat& quat)
				{
					T t = 1.0f - (quat.x * quat.x) - (quat.y * quat.y) - (quat.z * quat.z);
					if (t < 0.0) return (T)0.0;
					return (T)-sqrt(t);
				}
			};
		}
	}
}