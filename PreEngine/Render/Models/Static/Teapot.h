#ifndef TEAPOT_H
#define TEAPOT_H

#include "TeapotData.h"
#include "AbstractDrawableObject.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace Static
			{
				// NEEDS REWRITE :)
				class Teapot : public AbstractDrawableObject
				{
				private:
					unsigned int m_countOfFaces;

					unsigned int m_grid;

					glm::mat4 m_lidTransform;

				private:
					void GeneratePatches(float* v, float* n, float* tc, unsigned int* el, int grid);

					void BuildPatchReflect(int patchNum, float *B, float *dB, float *v, float *n, float *, unsigned int *el, int &index, int &elIndex, int &, int grid, bool reflectX, bool reflectY);

					void BuildPatch(glm::vec3 patch[][4], float *B, float *dB, float *v, float *n, float *, unsigned int *el, int &index, int &elIndex, int &, int grid, glm::mat3 reflect, bool invertNormal);

					void GetPatch(int patchNum, glm::vec3 patch[][4], bool reverseV);

					void ComputeBasisFunctions(float * B, float * dB, int grid);

					glm::vec3 Evaluate(int gridU, int gridV, float *B, glm::vec3 patch[][4]);

					glm::vec3 EvaluateNormal(int gridU, int gridV, float *B, float *dB, glm::vec3 patch[][4]);

					void MoveLid(int, float *, glm::mat4);

				public:
					Teapot(int grid, glm::mat4 lidTransform);

					virtual ~Teapot();

				public:
					void Init();

					void Render(GLenum how = GL_TRIANGLES);

					void RenderBoundingBox();

					void Delete();
				};
			}
		}
	}
}

#endif