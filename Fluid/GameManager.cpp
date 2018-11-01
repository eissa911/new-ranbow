#include <windows.h>
#include "GameManager.h"
#include "Offsets.h"
#include "Memory.h"
#include "GameRenderer.h"

namespace Engine {
	Array<Entity*> GameManager::GetEntities() {
		return *Memory::Ptr<Array<Entity*>*>(this, OFFSET_GameManager_EntityList);
	}

	GameManager* GameManager::GetInstance() {
		return *reinterpret_cast<GameManager**>(ADDRESS_GameManager + reinterpret_cast<uint64_t>(GetModuleHandle(NULL)));
	}

	Entity* GameManager::GetLocalPlayer() {
		Entity* pLocalPlayer = NULL;
		auto pGameManager = Engine::GameManager::GetInstance();
		auto pCamera = Engine::GameRenderer::GetInstance()->GetCamera();

		for(uint32_t i = 0; i < pGameManager->GetEntities().GetSize(); i++) {
			auto pEntity = pGameManager->GetEntities()[i];

			if(Memory::IsValidPtr<Entity>(pEntity)) {
				if(pCamera->GetViewTranslation().Distance(pEntity->GetHead()) < 0.1f)
					pLocalPlayer = pEntity;
			}
		}

		return pLocalPlayer;
	}
}