#ifndef CACHE_H
#define CACHE_H

#include "../Common.h"

namespace PreEngine
{
	namespace Core
	{
		namespace Caching
		{
			using namespace PreEngine::Core;

			template <class TypeKey, class TypeValue>
			class Cache
			{
			private:
				std::map<TypeKey, TypeValue> m_cacheData;

			public:
				Cache();

				virtual ~Cache();

			public:
				TypeValue Get(TypeKey key);

				bool Contains(TypeKey key);

				void Add(TypeKey key, TypeValue data);

				size_t GetCountOfItems() const;

				void Clear();
			};


			template <class TypeKey, class TypeValue>
			Cache<TypeKey, TypeValue>::Cache()
			{
			}

			template <class TypeKey, class TypeValue>
			Cache<TypeKey, TypeValue>::~Cache()
			{
			}

			template <class TypeKey, class TypeValue>
			TypeValue Cache<TypeKey, TypeValue>::Get(TypeKey key)
			{
				return m_cacheData[key];
			}

			template <class TypeKey, class TypeValue>
			bool Cache<TypeKey, TypeValue>::Contains(TypeKey key)
			{
				return m_cacheData.find(key) != m_cacheData.end();
			}

			template <class TypeKey, class TypeValue>
			void Cache<TypeKey, TypeValue>::Add(TypeKey key, TypeValue data)
			{
				m_cacheData.insert(std::make_pair(key, data));
			}

			template <class TypeKey, class TypeValue>
			size_t Cache<TypeKey, TypeValue>::GetCountOfItems() const
			{
				return m_cacheData.size();
			}

			template <class TypeKey, class TypeValue>
			void Cache<TypeKey, TypeValue>::Clear()
			{
				return m_cacheData.clear();
			}
		}
	}
}

#endif