#ifndef ISOUND_FACTORY_H
#define ISOUND_FACTORY_H

namespace PreEngine
{
	namespace Audio
	{
		class ISoundFactory
		{
		public:
			virtual ISound* CreateSoundFromWav(std::string filePath) = 0;

		public:
			virtual ~ISoundFactory() {}
		};
	}
}

#endif