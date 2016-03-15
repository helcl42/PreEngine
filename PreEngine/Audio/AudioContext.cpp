#include "AudioContext.h"

namespace PreEngine
{
	namespace Audio
	{
		AudioContext::AudioContext()
		{
		}

		AudioContext::AudioContext(std::string deviceName)
			: m_deviceName(deviceName)
		{
		}

		AudioContext::~AudioContext()
		{
		}

		bool AudioContext::Init()
		{
			if (m_deviceName == "") m_device = alcOpenDevice(NULL);
			else m_device = alcOpenDevice(m_deviceName.c_str());
			if (!m_device) throw new AudioException("OpenAL: could not open device");

			m_context = alcCreateContext(m_device, NULL);
			if (!m_context) throw new AudioException("OpenAL: could not create context");

			ALboolean result = alcMakeContextCurrent(m_context);
			if (result == ALC_FALSE) throw new AudioException("OpenAL: could not make context current");

			result = alIsExtensionPresent("AL_SOFT_source_length");
			if (result == ALC_FALSE) throw new AudioException("Required AL_SOFT_source_length not supported");

			result = alcIsExtensionPresent(m_device, "ALC_EXT_thread_local_context");
			if (result == ALC_FALSE) throw new AudioException("Required ALC_EXT_thread_local_contex not supported - exiting");
			
			return true;
		}

		void AudioContext::Update(float deltaTime)
		{
		}

		void AudioContext::ShutDown()
		{
			alcMakeContextCurrent(NULL);
			alcDestroyContext(m_context);
			alcCloseDevice(m_device);
		}

		void AudioContext::MakeContextMain()
		{
			ALboolean result = alcMakeContextCurrent(m_context);
			if (result == ALC_FALSE) throw new AudioException("OpenAL: could not make context current");
		}

		void AudioContext::DumpOutputDevices()
		{
			const ALchar *deviceList = alcGetString(NULL, ALC_ALL_DEVICES_SPECIFIER);
			if (deviceList)
			{
				std::cout << "Available Audio Output Devices are:"<< std::endl;

				while (*deviceList)
				{
					std::cout << deviceList << std::endl;
					deviceList += strlen(deviceList) + 1;
				}
			}
			else
			{
				std::cout << "No Audio Output devices available." << std::endl;
			}
		}

		std::string AudioContext::GetDeviceName() const
		{
			return m_deviceName;
		}

		ALCcontext* AudioContext::GetContext() const
		{
			return m_context;
		}

		ALCdevice* AudioContext::GetDevice() const
		{
			return m_device;
		}
	}
}
