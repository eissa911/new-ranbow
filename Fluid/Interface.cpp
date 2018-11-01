#include <windows.h>
#include "Offsets.h"
#include "Memory.h"
#include "Interface.h"

namespace Engine {
	Interface* Interface::GetInstance() {
		return *reinterpret_cast<Interface**>(ADDRESS_Interface + reinterpret_cast<uint64_t>(GetModuleHandle(NULL)));
	}

	bool Interface::IsInGame() {
		auto Interface = Memory::Ptr<void**>(this, OFFSET_Interface);
		auto InCross = Memory::Ptr<void**>(Interface, OFFSET_Interface_INCROSS);

		if(!Memory::IsValidPtr(InCross))
			return false;

		if(InCross == NULL)
			return false;

		return true;
	}
}