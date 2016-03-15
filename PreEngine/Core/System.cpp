#include "System.h"

namespace PreEngine
{
	namespace Core
	{
		System::System()
		{
		}

		System::~System()
		{
		}

		bool System::Init() {
			std::cout << "Initializing" << std::endl;
			return true;
		}

		void System::Update(float deltaTime) {
		}

		void System::ShutDown() {
			std::cout << "ShuttingDown" << std::endl;
		}
	}
}