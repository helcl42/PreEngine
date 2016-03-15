#ifndef OBJECT_H
#define OBJECT_H

#include "Common.h"

namespace PreEngine
{
	namespace Core
	{
		using namespace PreEngine::Utils;

		template <class ObjectType>
		class Object
		{
		protected:
			std::type_index m_typeIndex;

			std::string m_name;

			std::string m_canonicalName;

			uint64_t m_id;

		public:			
			Object();

			virtual ~Object();

		public:
			size_t GetHashCode() const;

			uint64_t GetId() const;

			std::string GetType() const;

			std::string GetCanonicalName() const;

			std::string GetName() const;

			std::type_index GetTypeIndex() const;

		protected:			
			void SetName(std::string name);
		};


		template <class ObjectType>
		Object<ObjectType>::Object()
			: m_typeIndex(typeid(ObjectType))
		{
			m_id = IDGenerator::GetInstance().GetNewId();
#ifdef _DEBUG
			PreEngine::Utils::Log::Logger::GetInstance().Debug() << "Id: " << m_id << " HashCode: " <<  m_typeIndex.hash_code() << " Type: " << std::string(m_typeIndex.name());
#endif
			m_name = StringUtils::GetTypeName(GetType());
			m_canonicalName = StringUtils::GetCanonicalTypeName(GetType());
		}

		template <class ObjectType>
		Object<ObjectType>::~Object()
		{
		}

		template <class ObjectType>
		uint64_t Object<ObjectType>::GetId() const
		{
			return m_id;
		}

		template <class ObjectType>
		size_t Object<ObjectType>::GetHashCode() const
		{
			return m_typeIndex.hash_code();
		}

		template <class ObjectType>
		std::string Object<ObjectType>::GetType() const
		{
			return std::string(m_typeIndex.name());
		}

		template <class ObjectType>
		std::type_index Object<ObjectType>::GetTypeIndex() const
		{
			return m_typeIndex;
		}

		template <class ObjectType>
		std::string Object<ObjectType>::GetName() const
		{
			return m_name;
		}

		template <class ObjectType>
		std::string Object<ObjectType>::GetCanonicalName() const
		{
			return m_canonicalName;
		}

		template <class ObjectType>
		void Object<ObjectType>::SetName(std::string name)
		{
			m_name = name;
		}
	}
}

#endif
