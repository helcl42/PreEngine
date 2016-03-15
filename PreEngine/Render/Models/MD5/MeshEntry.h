#ifndef MESH_ENTRY_H
#define MESH_ENTRY_H

#define INVALID_MATERIAL 0xFFFFFFFF

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace MD5
			{
				struct MeshEntry
				{
					unsigned int numberOfIndices;

					unsigned int baseVertex;

					unsigned int baseIndex;

					unsigned int materialIndex;

					MeshEntry()
						: numberOfIndices(0), baseVertex(0), baseIndex(0), materialIndex(INVALID_MATERIAL)
					{
					}

					virtual ~MeshEntry()
					{
					}
				};
			}
		}
	}
}

#endif