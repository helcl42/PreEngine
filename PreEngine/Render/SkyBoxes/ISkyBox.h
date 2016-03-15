#ifndef ISKYBOX_H
#define ISKYBOX_H

namespace PreEngine
{
	namespace Render
	{
		namespace SkyBoxes
		{
			class ISkyBox
			{
			public:
				virtual void Render() = 0;

				virtual void Delete() = 0;

			public:
				virtual ~ISkyBox() {}
			};
		}
	}
}

#endif
