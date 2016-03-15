#ifndef IFONT_H
#define IFONT_H

#include "../Shaders/IShaderProgram.h"

namespace PreEngine
{
	namespace Render
	{
		namespace Fonts
		{
			using namespace PreEngine::Render::Shaders;

			class IFont
			{
			public:
				virtual unsigned int GetTextWidth(const std::string& text, int pxSize) = 0;

				virtual unsigned int GetTextHeight(const std::string& text, int pxSize) = 0;

				virtual void Print(const std::string& text, int x, int y, int pxSize = -1) = 0;

				virtual void Delete() = 0;

				virtual void SetShaderProgram(IShaderProgram* shaderProgram) = 0;

			public:
				virtual ~IFont() {}
			};
		}
	}
}

#endif