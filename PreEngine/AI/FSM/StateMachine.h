#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "IState.h"

namespace PreEngine
{
	namespace Utils
	{
		namespace AI
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

				void  Update();

				void  ChangeState(IState<ObjectType>* newState);

				void  RevertToPreviousState();

				bool  IsInState(const IState<ObjectType>& st) const;

				IState<ObjectType>* CurrentState() const;

				IState<ObjectType>* GlobalState() const;

				IState<ObjectType>* PreviousState() const;
			};

			template <class ObjectType>
			StateMachine<ObjectType>::StateMachine(ObjectType* owner)
				: m_owner(owner), m_pCurrentState(NULL), m_pPreviousState(NULL), m_pGlobalState(NULL)
			{
			}

			template <class ObjectType>
			StateMachine<ObjectType>::~StateMachine()
			{
			}

			template <class ObjectType>
			void StateMachine<ObjectType>::SetCurrentState(IState<ObjectType>* state)
			{
				m_pCurrentState = state;
			}

			template <class ObjectType>
			void StateMachine<ObjectType>::SetGlobalState(IState<ObjectType>* state)
			{
				m_pGlobalState = state;
			}

			template <class ObjectType>
			void StateMachine<ObjectType>::SetPreviousState(IState<ObjectType>* state)
			{
				m_pPreviousState = state;
			}

			template <class ObjectType>
			void StateMachine<ObjectType>::Update()
			{
				if (m_globalState)   m_pGlobalState->Execute(m_owner);

				if (m_currentState) m_pCurrentState->Execute(m_owner);
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
				ChangeState(m_pPreviousState);
			}

			template <class ObjectType>
			bool StateMachine<ObjectType>::IsInState(const IState<ObjectType>& st)const
			{
				return typeid(*m_pCurrentState) == typeid(st);
			}

			template <class ObjectType>
			IState<ObjectType>* StateMachine<ObjectType>::CurrentState()  const
			{
				return m_pCurrentState;
			}

			template <class ObjectType>
			IState<ObjectType>* StateMachine<ObjectType>::GlobalState()   const
			{
				return m_pGlobalState;
			}

			template <class ObjectType>
			IState<ObjectType>* StateMachine<ObjectType>::PreviousState() const
			{
				return m_pPreviousState;
			}
		}
	}
}

#endif