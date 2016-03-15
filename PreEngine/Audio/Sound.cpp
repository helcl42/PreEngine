#include "Sound.h"

namespace PreEngine
{
	namespace Audio
	{
		Sound::Sound()
			: Sound(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::mat2x3(0.0, 0.0, -1.0, 0.0, 1.0, 0.0))
		{
		}

		Sound::Sound(glm::vec3 sourcePosition, glm::vec3 sourceVelocity, glm::vec3 listenerPosition, glm::vec3 listenerVelocity, glm::mat2x3 listenerOrientation)
		{
			for (unsigned int i = 0; i < 3; i++) m_sourcePosition[i] = sourcePosition[i];
			for (unsigned int i = 0; i < 3; i++) m_sourceVelocity[i] = sourceVelocity[i];
			for (unsigned int i = 0; i < 3; i++) m_listenerPosition[i] = listenerPosition[i];
			for (unsigned int i = 0; i < 3; i++) m_listenerVelocity[i] = listenerVelocity[i];

			for (unsigned int i = 0, index = 0; i < 2; i++)
			{
				for (unsigned int j = 0; j < 3; j++)
				{
					m_listenerOrientation[index] = listenerOrientation[i][j];
					index++;
				}
			}
		}

		Sound::~Sound()
		{
			SAFE_DELETE_ARRAY(m_data);
		}

		void Sound::Play(float gain, bool loop)
		{
			if (m_isPlaying) Stop();

			alGenBuffers(1, &m_buffer);
			alGenSources(1, &m_source);
			if (alGetError() != AL_NO_ERROR) throw new AudioException("Error GenSource");

			alBufferData(m_buffer, m_format, m_data, m_dataSize, m_sampleRate);
			if (alGetError() != AL_NO_ERROR) throw new AudioException("Error loading ALBuffer");

			alListenerfv(AL_POSITION, m_listenerPosition);
			alListenerfv(AL_VELOCITY, m_listenerVelocity);
			alListenerfv(AL_ORIENTATION, m_listenerOrientation);

			alSourcei(m_source, AL_BUFFER, m_buffer);
			alSourcef(m_source, AL_PITCH, 1.0f);
			alSourcef(m_source, AL_GAIN, gain);
			alSourcefv(m_source, AL_POSITION, m_sourcePosition);
			alSourcefv(m_source, AL_VELOCITY, m_sourceVelocity);
			alSourcei(m_source, AL_LOOPING, loop);

			alSourcePlay(m_source);
			if (alGetError() != AL_NO_ERROR) throw new AudioException("Error playing sound");
			m_isPlaying = true;
		}

		void Sound::Stop()
		{
			alDeleteSources(1, &m_source);
			alDeleteBuffers(1, &m_buffer);
			m_isPlaying = false;
		}

		bool Sound::IsPlaying() const
		{
			return m_isPlaying;
		}

		bool Sound::Seek(int64_t timeStamp)
		{
			return false;
		}
	}
}
