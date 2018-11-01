#include <windows.h>
#include "GameRenderer.h"
#include "Offsets.h"
#include "Memory.h"

namespace Engine {
	Camera* GameRenderer::GetCamera() {
		if(!Memory::IsValidPtr<GameRenderer>(this))
			return nullptr;

		auto pGameRenderer = *Memory::Ptr<void**>(this, (OFFSET_GameManager_DEREF));F

		auto pEngineLink = *Memory::Ptr<void**>(pGameRenderer, (OFFSET_GameManager_EngineLINK));

		if(!Memory::IsValidPtr(pEngineLink))
			return nullptr;

		auto pEngine = *Memory::Ptr<void**>(pEngineLink, (OFFSET_EngineLINK_Engine));

		if(!Memory::IsValidPtr(pEngine))
			return nullptr;

		return *Memory::Ptr<Camera**>(pEngine, (OFFSET_Engine_Camera));
	}

	GameRenderer* GameRenderer::GetInstance() {
		return *reinterpret_cast<GameRenderer**>(ADDRESS_GameRenderer + reinterpret_cast<uint64_t>(GetModuleHandle(NULL)));
	}
}