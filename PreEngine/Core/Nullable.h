#ifndef NULLABLE_H
#define NULLABLE_H

#include "Common.h"

namespace PreEngine
{
	namespace Core
	{
		template<class Type>
		class Nullable
		{
		private:
			const Type* m_value;

			bool m_isNull;

		public:
			Nullable(const Type* value);

			Nullable();

			virtual ~Nullable();

		public:
			bool IsNull() const
			{
				return m_isNull;
			}
		};

		template<class Type>
		Nullable<Type>::Nullable(const Type* value)
			: m_value(value), m_isNull(false)
		{
		}

		template<class Type>
		Nullable<Type>::Nullable()
			: m_isNull(true)
		{
		}

		template<class Type>
		Nullable<Type>::~Nullable()
		{
		}
	}
}

#endif