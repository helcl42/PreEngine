#ifndef __SINGLETON_H__
#define __SINGLETON_H__

namespace PreEngine
{
	namespace Core
	{
		namespace Patterns
		{
			template <class ChildType>
			class Singleton
			{
			private:
				friend ChildType;

			private:
				static ChildType s_instance;

			private:
				Singleton(const Singleton&);

				Singleton(Singleton&&);

				Singleton& operator=(const Singleton&);

				Singleton& operator=(Singleton&&);

				Singleton()
				{
				}

			public:
				static ChildType& GetInstance()
				{
					return s_instance;
				}

				virtual ~Singleton()
				{
				}
			};

			template <class ChildType>
			ChildType Singleton<ChildType>::s_instance;
		}
	}
}

#endif
