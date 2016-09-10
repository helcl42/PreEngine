#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "IState.h"

namespace PreEngine
{
	namespace Core
	{
		namespace Patterns
		{
			template <class ObjectType>
			class StateMachine
			{
			protected:
				ObjectType*          m_owner;

				IState<ObjectType>*   m_currentState;

				IState<ObjectType>*   m_previousState;

				IState<ObjectType>*   m_globalState;


			public:
				StateMachine(ObjectType* owner);

				virtual ~StateMachine();

			public:
				void SetCurrentState(IState<ObjectType>* state);

				void SetGlobalState(IState<ObjectType>* state);

				void SetPreviousState(IState<ObjectType>* state);

				void Update();

				void ChangeState(IState<ObjectType>* newState);

				void RevertToPreviousState();

				bool IsInState(const IState<ObjectType>* st) const;

				IState<ObjectType>* GetCurrentState() const;

				IState<ObjectType>* GetGlobalState() const;

				IState<ObjectType>* GetPreviousState() const;
			};

			template <class ObjectType>
			StateMachine<ObjectType>::StateMachine(ObjectType* owner)
				: m_owner(owner), m_currentState(NULL), m_previousState(NULL), m_globalState(NULL)
			{
			}

			template <class ObjectType>
			StateMachine<ObjectType>::~StateMachine()
			{
			}

			template <class ObjectType>
			void StateMachine<ObjectType>::SetCurrentState(IState<ObjectType>* state)
			{
				m_currentState = state;
			}

			template <class ObjectType>
			void StateMachine<ObjectType>::SetGlobalState(IState<ObjectType>* state)
			{
				m_globalState = state;
			}

			template <class ObjectType>
			void StateMachine<ObjectType>::SetPreviousState(IState<ObjectType>* state)
			{
				m_previousState = state;
			}

			template <class ObjectType>
			void StateMachine<ObjectType>::Update()
			{
				if (m_globalState) m_globalState->Execute(m_owner);

				if (m_currentState) m_currentState->Execute(m_owner);
			}

			template <class ObjectType>
			void StateMachine<ObjectType>::ChangeState(IState<ObjectType>* newState)
			{
				m_previousState = m_currentState;

				m_currentState->Exit(m_owner);

				m_currentState = newState;

				m_currentState->Enter(m_owner);
			}

			template <class ObjectType>
			void StateMachine<ObjectType>::RevertToPreviousState()
			{
				ChangeState(m_previousState);
			}

			template <class ObjectType>
			bool StateMachine<ObjectType>::IsInState(const IState<ObjectType>* st) const
			{
				if (m_currentState == NULL) return false;
				return m_currentState == st;
			}

			template <class ObjectType>
			IState<ObjectType>* StateMachine<ObjectType>::GetCurrentState() const
			{
				return m_currentState;
			}

			template <class ObjectType>
			IState<ObjectType>* StateMachine<ObjectType>::GetGlobalState() const
			{
				return m_globalState;
			}

			template <class ObjectType>
			IState<ObjectType>* StateMachine<ObjectType>::GetPreviousState() const
			{
				return m_previousState;
			}
		}
	}
}

#endif