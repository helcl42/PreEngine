#ifndef VERTEX_BONE_DATA_H
#define VERTEX_BONE_DATA_H

#define NUM_BONES_PER_VEREX 4

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace MD5
			{
				struct VertexBoneData
				{
					unsigned int IDs[NUM_BONES_PER_VEREX];
					float weights[NUM_BONES_PER_VEREX];

					VertexBoneData()
					{
						Reset();
					}

					virtual ~VertexBoneData()
					{
					}

					void Reset()
					{
						ZERO_MEM(IDs);
						ZERO_MEM(weights);
					}

					void AddBoneData(unsigned int BoneID, float Weight)
					{
						for (unsigned int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(IDs); i++)
						{
							if (weights[i] == 0.0)
							{
								IDs[i] = BoneID;
								weights[i] = Weight;
								return;
							}
						}

						// should never get here - more bones than we have space for
						assert(0);
					}
				};
			}
		}
	}
}

#endif