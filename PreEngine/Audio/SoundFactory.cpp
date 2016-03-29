#include "SoundFactory.h"


namespace PreEngine
{
	namespace Audio
	{
		SoundFactory::SoundFactory()
		{
		}

		SoundFactory::~SoundFactory()
		{
		}

		ALenum SoundFactory::GetFormat(short bitsPerSample, short channels)
		{
			if (bitsPerSample == 8)
			{
				if (channels == 1) return AL_FORMAT_MONO8;
				else if (channels == 2) return AL_FORMAT_STEREO8;
			}
			else if (bitsPerSample == 16)
			{
				if (channels == 1) return AL_FORMAT_MONO16;
				else if (channels == 2) return AL_FORMAT_STEREO16;
			}
			else if (bitsPerSample == 32)
			{
				if (channels == 1) return AL_FORMAT_MONO_FLOAT32;
				else if (channels == 2) return AL_FORMAT_STEREO_FLOAT32;
			}
			return 0;
		}

		ISound* SoundFactory::CreateSoundFromWav(std::string filePath)
		{
			FileReader fileReader(filePath, std::ios::binary);
			if (!fileReader.IsOpen()) throw AudioException("Failed to open file");

			Sound* sound = new Sound();

			sound->m_filePath = filePath;

			char type[4];
			fileReader.ReadBytes(type, 4);
			if (type[0] != 'R' || type[1] != 'I' || type[2] != 'F' || type[3] != 'F') throw AudioException("No RIFF");

			sound->m_size = fileReader.ReadLong();

			fileReader.ReadBytes(type, 4);
			if (type[0] != 'W' || type[1] != 'A' || type[2] != 'V' || type[3] != 'E') throw AudioException("Not WAVE??!!");

			fileReader.ReadBytes(type, 4);
			if (type[0] != 'f' || type[1] != 'm' || type[2] != 't' || type[3] != ' ') throw AudioException("Not fmt??!!");

			sound->m_chunkSize = fileReader.ReadLong();
			sound->m_formatType = fileReader.ReadShort();
			sound->m_channels = fileReader.ReadShort();
			sound->m_sampleRate = fileReader.ReadLong();
			sound->m_avgBytesPerSec = fileReader.ReadLong();
			sound->m_bytesPerSample = fileReader.ReadShort();
			sound->m_bitsPerSample = fileReader.ReadShort();

			fileReader.ReadBytes(type, 4);
			if (type[0] == 'L' && type[1] == 'I' && type[2] == 'S' && type[3] == 'T')
			{
				fileReader.ReadBytes(type, 4);
				for (unsigned int j = 0, siginificace = 1; j < 4; j++, siginificace * 255)
				{
					fileReader.Ignore(type[j] * siginificace);
				}
			}
			
			fileReader.ReadBytes(type, 4);
			if (type[0] != 'd' || type[1] != 'a' || type[2] != 't' || type[3] != 'a') throw AudioException("Invalid DATA");

			sound->m_dataSize = fileReader.ReadLong();

			sound->m_format = GetFormat(sound->m_bitsPerSample, sound->m_channels);
			if (!sound->m_format) throw AudioException("Wrong format");

			sound->m_data = new uint8_t[sound->m_dataSize];
			fileReader.ReadBytes(sound->m_data, sound->m_dataSize);

			return sound;
		}
	}
}