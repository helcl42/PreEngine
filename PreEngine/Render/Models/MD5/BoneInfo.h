#ifndef BONE_INFO_H
#define BONE_INFO_H

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace MD5
			{
				struct BoneInfo
				{
					glm::mat4 boneOffset;

					glm::mat4 finalTransformation;

					BoneInfo()
					{
					}

					virtual ~BoneInfo()
					{
					}
				};
			}
		}
	}
}

#endif