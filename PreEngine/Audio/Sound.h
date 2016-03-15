#ifndef AUDIO_H
#define AUDIO_H

#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alext.h"

#include "../Core/Common.h"
#include "../Utils/IO/FileReader.h"

#include "ISound.h"
#include "AudioException.h"

namespace PreEngine
{
	namespace Audio
	{
		using namespace PreEngine::Utils::IO;

		class SoundFactory;

		class Sound : public ISound
		{
		private:
			friend class SoundFactory;

		private:
			unsigned long m_size, m_chunkSize;

			short m_formatType, m_channels;

			unsigned long m_sampleRate, m_avgBytesPerSec;

			short m_bytesPerSample, m_bitsPerSample;

			uint8_t* m_data;

			unsigned long m_dataSize;

			ALenum m_format;

			std::string m_filePath;

			ALuint m_source;

			ALuint m_buffer;

			ALfloat m_sourcePosition[3];

			ALfloat m_sourceVelocity[3];

			ALfloat m_listenerPosition[3];

			ALfloat m_listenerVelocity[3];

			ALfloat m_listenerOrientation[6];

			bool m_isPlaying = false;

			float m_gain = 1.0f;

		public:
			Sound();

			Sound(glm::vec3 sourcePosition, glm::vec3 sourceVelocity, glm::vec3 listenerPosition, glm::vec3 listenerVelocity, glm::mat2x3 listenerOrientation);

			virtual ~Sound();

		public:
			void Play(float gain, bool loop = false);

			void Stop();

			bool IsPlaying() const;

			bool Seek(int64_t timeStamp);
		};
	}
}

#endif