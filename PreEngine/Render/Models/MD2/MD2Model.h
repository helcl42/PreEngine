#ifndef MD2_MODEL_H
#define MD2_MODEL_H

#include "../../VertexBufferObjects/VertexBufferObject.h"
#include "../../Shaders/ShaderProgram.h"
#include "../../Textures/TextureFactory.h"

#include "MD2ModelCommon.h"
#include "../IAnimatedModel.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			namespace MD2
			{
				using namespace PreEngine::Render::VertexBufferObjects;
				using namespace PreEngine::Render::Textures;
				using namespace PreEngine::Render::Shaders;

				class MD2Model : public IAnimatedModel
				{
				private:
					friend class MD2ModelFactory;

				private:
					bool m_defaultTexturesEnabled;

					unsigned int m_vertexArrayObject;

					std::vector<IVertexBufferObject*> m_vboFrameVertices;

					IVertexBufferObject* m_vboTextureCoords;

					std::vector<int> m_renderModes;

					std::vector<int> m_numberOfRenderedVertices;

					ITexture* m_texture;

					IShaderProgram* m_animationProgram;

				public:
					static AnimationData animlist[MAX_ANIMATIONS];

				public:
					MD2Model();

					virtual ~MD2Model();

				public:
					void SetDefaultTexturesEnabled(bool enabled);

					bool IsDefaultTexturesEnabled() const;

					void SetShaderProgram(IShaderProgram* program);

					IShaderProgram* GetShaderProgram() const;

					void Init();

					void ShutDown();

					void Render(AnimationState* animState);

					AnimationState StartAnimation(AnimationType type);

					void UpdateAnimation(AnimationState* animState, float elapsedTime);

					void PauseAnimation();

					void StopAnimation();
				};
			}
		}
	}
}

#endif