#ifndef OBSERVABLE_BASE_H
#define OBSERVABLE_BASE_H

#include "Common.h"

namespace PreEngine
{
	namespace Core
	{
		template <class ObserverType>
		class Observer
		{
		protected:
			std::vector<ObserverType*> m_observables;

		public:
			Observer();

			virtual ~Observer();

		public:
			bool RegisterListener(ObserverType* listener);

			bool UnregisterListener(ObserverType* listener);

			const std::vector<ObserverType*>& GetObservables() const;
		};

		template <class ObserverType>
		Observer<ObserverType>::Observer()
		{
		}

		template <class ObserverType>
		Observer<ObserverType>::~Observer()
		{
		}

		template <class ObserverType>
		bool Observer<ObserverType>::RegisterListener(ObserverType* listener)
		{
			for (std::vector<ObserverType*>::const_iterator ci = m_observables.cbegin(); ci != m_observables.cend(); ++ci)
			{
				if (listener == *ci) return false;
			}

			m_observables.push_back(listener);
			return true;
		}

		template <class ObserverType>
		bool Observer<ObserverType>::UnregisterListener(ObserverType* listener)
		{
			bool found = false;
			for (std::vector<ObserverType*>::const_iterator ci = m_observables.cbegin(); ci != m_observables.cend(); ++ci)
			{
				if (*ci == listener)
				{
					m_observables.erase(ci);
					found = true;
				}
			}
			return found;
		}

		template <class ObserverType>
		const std::vector<ObserverType*>& Observer<ObserverType>::GetObservables() const
		{
			return m_observables;
		}
	}
}

#endif