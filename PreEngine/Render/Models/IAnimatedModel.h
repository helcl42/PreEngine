#ifndef IANIMATED_MODEL_H
#define IANIMATED_MODEL_H

namespace PreEngine
{
	namespace Render
	{
		namespace Models
		{
			using namespace PreEngine::Render::Shaders;
			using namespace PreEngine::Render::Models::MD2;

			class IAnimatedModel
			{
			public:
				virtual void SetShaderProgram(IShaderProgram* program) = 0;

				virtual IShaderProgram* GetShaderProgram() const = 0;

				virtual void Init() = 0;

				virtual void ShutDown() = 0;

				virtual void Render(AnimationState* animState) = 0;

				virtual AnimationState StartAnimation(AnimationType type) = 0;

				virtual void UpdateAnimation(AnimationState* animState, float elapsedTime) = 0;

				virtual void PauseAnimation() = 0;

				virtual void StopAnimation() = 0;

				virtual bool IsDefaultTexturesEnabled() const = 0;

				virtual void SetDefaultTexturesEnabled(bool enabled) = 0;
			};
		}
	}
}

#endif