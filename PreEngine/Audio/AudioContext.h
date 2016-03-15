#ifndef AL_AUDIO_CONTEXT_H
#define AL_AUDIO_CONTEXT_H

#define AL_ALEXT_PROTOTYPES 0

extern "C" {
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>
}

#include "../Core/Common.h"
#include "../Core/System.h"
#include "AudioException.h"

namespace PreEngine
{
	namespace Audio
	{
		using namespace PreEngine::Core;		

		class AudioContext : public System
		{
		private:
			ALCdevice* m_device = NULL;

			ALCcontext* m_context = NULL;

			std::string m_deviceName;

		public:
			AudioContext();

			AudioContext(std::string deviceName);

			virtual ~AudioContext();

		public:
			bool Init();

			void Update(float deltaTime);

			void ShutDown();

			void MakeContextMain();

			void DumpOutputDevices();

			std::string GetDeviceName() const;

			ALCcontext* GetContext() const;

			ALCdevice* GetDevice() const;
		};
	}
}

#endif