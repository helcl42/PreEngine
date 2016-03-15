#ifndef ISTATE_H
#define ISTATE_H

namespace PreEngine
{
	namespace AI
	{
		namespace FSM
		{
			template <class ObjectType>
			class IState
			{
			public:
				virtual void Enter(ObjectType* object) = 0;

				virtual void Execute(ObjectType* object) = 0;

				virtual void Exit(ObjectType* object) = 0;

			public:
				virtual ~IState() {}
			};
		}
	}
}

#endif