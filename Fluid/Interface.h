#pragma once

namespace Engine {
	class Interface {
	public:
		static Interface* GetInstance();
		bool IsInGame();
	};
}