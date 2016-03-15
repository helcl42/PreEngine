#ifndef ISOUND_H
#define ISOUND_H

namespace PreEngine
{
	namespace Audio
	{
		class ISound
		{
		public:
			virtual void Play(float gain, bool loop = false) = 0;

			virtual void Stop() = 0;
		
			virtual bool IsPlaying() const = 0;

			virtual bool Seek(int64_t timeStamp) = 0;

		public:
			virtual ~ISound() {}
		};
	}
}

#endif