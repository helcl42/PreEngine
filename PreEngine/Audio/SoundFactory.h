#ifndef SOUND_FACTORY_H
#define SOUND_FACTORY_H

#include "../Core/Common.h"
#include "Sound.h"
#include "ISoundFactory.h"

namespace PreEngine
{
	namespace Audio
	{
		// now supports .wav only, no more options -> TEMPORARY use FFMPEG to support any format
		class SoundFactory : public ISoundFactory
		{
		public:
			SoundFactory();

			virtual ~SoundFactory();

		private:
			ALenum GetFormat(short bitsPerSample, short channels);

		public:
			ISound* CreateSoundFromWav(std::string filePath);
		};
	}
}

#endif