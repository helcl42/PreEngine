#ifndef GLOBAL_CACHE_H
#define GLOBAL_CACHE_H

#include "../Common.h"

namespace PreEngine
{
	namespace Core
	{
		namespace Caching
		{
			using namespace PreEngine::Core;

			template <class TypeKey, class TypeValue>
			class GlobalCache
			{
			private:
				std::map<TypeKey, TypeValue> m_cacheData;

				static GlobalCache<TypeKey, TypeValue> s_instance;

			private:
				GlobalCache();

			public:
				static GlobalCache<TypeKey, TypeValue>& GetInstance();

				virtual ~GlobalCache();

			public:
				TypeValue Get(TypeKey key);

				std::map<TypeKey, TypeValue>& GetAll();

				bool Contains(TypeKey key);

				void Add(TypeKey key, TypeValue data);

				size_t GetCountOfItems() const;				
			};

			template <class TypeKey, class TypeValue>
			GlobalCache<TypeKey, TypeValue> GlobalCache<TypeKey, TypeValue>::s_instance;

			template <class TypeKey, class TypeValue>
			GlobalCache<TypeKey, TypeValue>& GlobalCache<TypeKey, TypeValue>::GetInstance()
			{
				return s_instance;
			}

			template <class TypeKey, class TypeValue>
			GlobalCache<TypeKey, TypeValue>::GlobalCache()
			{
			}

			template <class TypeKey, class TypeValue>
			GlobalCache<TypeKey, TypeValue>::~GlobalCache()
			{
			}

			template <class TypeKey, class TypeValue>
			TypeValue GlobalCache<TypeKey, TypeValue>::Get(TypeKey key)
			{
				return m_cacheData[key];
			}

			template <class TypeKey, class TypeValue>
			std::map<TypeKey, TypeValue>& GlobalCache<TypeKey, TypeValue>::GetAll()
			{
				return m_cacheData;
			}

			template <class TypeKey, class TypeValue>
			bool GlobalCache<TypeKey, TypeValue>::Contains(TypeKey key)
			{
				return m_cacheData.find(key) != m_cacheData.end();
			}

			template <class TypeKey, class TypeValue>
			void GlobalCache<TypeKey, TypeValue>::Add(TypeKey key, TypeValue data)
			{
				m_cacheData.insert(std::make_pair(key, data));
			}

			template <class TypeKey, class TypeValue>
			size_t GlobalCache<TypeKey, TypeValue>::GetCountOfItems() const
			{
				return m_cacheData.size();
			}
		}
	}
}

#endif