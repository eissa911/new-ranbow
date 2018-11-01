#include "Main.h"
#include <windows.h>
#include "Entity.h"
#include "GameManager.h"
#include "GameRenderer.h"
#include "Interface.h"
#include "Settings.h"
#include <iostream>
#include <string>

// Handles text attributes within the console
class ConsoleAttr {
	friend std::ostream& operator<<(std::ostream& out, ConsoleAttr attr) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attr.value);
		return out;
	}
public:
	explicit ConsoleAttr(WORD attributes) : value(attributes) {
	}
private:
	WORD value;
};
#define FOREGROUND_WHITE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)

// Handles redrawing the menu after a change has occured
void drawMenu() {
	system("cls");

	ConsoleAttr reset = ConsoleAttr(FOREGROUND_WHITE);

	ConsoleAttr cavStatus = (Settings::GetInstance()->esp) ? (ConsoleAttr(FOREGROUND_GREEN)) : (ConsoleAttr(FOREGROUND_RED));
	std::string esp = (Settings::GetInstance()->esp) ? ("ENABLED") : ("DISABLED");

	ConsoleAttr steadyShootStatus = (Settings::GetInstance()->noRecoilSpread) ? (ConsoleAttr(FOREGROUND_GREEN)) : (ConsoleAttr(FOREGROUND_RED));
	std::string noRecoilSpread = (Settings::GetInstance()->noRecoilSpread) ? ("ENABLED") : ("DISABLED");

	ConsoleAttr lockShootStatus = (Settings::GetInstance()->lockShootBot) ? (ConsoleAttr(FOREGROUND_GREEN)) : (ConsoleAttr(FOREGROUND_RED));
	std::string lockShootBot = (Settings::GetInstance()->lockShootBot) ? ("ENABLED") : ("DISABLED");

	std::string box = (Settings::GetInstance()->lockShootBotbox == 0) ? ("CHEST") : (Settings::GetInstance()->lockShootBotbox == 1 ? ("NECK") : ("HEAD"));

	ConsoleAttr viewStatus = (Settings::GetInstance()->lockShootBotFOV == Settings::GetInstance()->lockShootBotFOVMin || Settings::GetInstance()->lockShootBotFOV == Settings::GetInstance()->lockShootBotFOVMax) ? (ConsoleAttr(FOREGROUND_RED)) : (ConsoleAttr(FOREGROUND_GREEN));
	ConsoleAttr speedStatus = (Settings::GetInstance()->lockShootBotSpeed == Settings::GetInstance()->lockShootBotSpeedMin || Settings::GetInstance()->lockShootBotSpeed == Settings::GetInstance()->lockShootBotSpeedMax) ? (ConsoleAttr(FOREGROUND_RED)) : (ConsoleAttr(FOREGROUND_GREEN));


	std::cout << "Nation R6S Unknowncheats.me" << std::endl;
	std::cout << "-------------------------------------------------------------------" << std::endl;
	std::cout << "[F1] CAV: " << cavStatus << esp << reset << std::endl;
	std::cout << "[F2] Steady Shoot: " << steadyShootStatus << noRecoilSpread << reset << std::endl;
	std::cout << "[F3] Lock Shoot: " << lockShootStatus << lockShootBot << reset << std::endl;
	std::cout << "[F4] Box: " << box << std::endl;
	std::cout << "[F5|F6] View: " << viewStatus << std::to_string(Settings::GetInstance()->lockShootBotFOV) << reset << std::endl;
	std::cout << "[F7|F8] Speed: " << speedStatus << std::to_string(Settings::GetInstance()->lockShootBotSpeed) << reset << std::endl;


	Sleep(100);
}

void Main::Start() {
	AllocConsole();
	freopen("CON", "w", stdout);

	drawMenu();

	// Other variables
	Engine::Entity* target = 0;
	Engine::Entity* closestTarget = 0;
	float distance;
	bool writeNoRecoilSpread = false;
	bool writeESP = false;
	int timer = 0;
	int CANO = target->CAN();
	// Main loop
	while(true) {
		// ESP toggles
		if(GetAsyncKeyState(Settings::GetInstance()->espToggle)) {
			Settings::GetInstance()->esp = (Settings::GetInstance()->esp) ? (false) : (true);
			Settings::GetInstance()->entitiesSet = 0;
			drawMenu();
		}

		// No recoil/spread toggles
		if(GetAsyncKeyState(Settings::GetInstance()->noRecoilSpreadToggle)) {
			Settings::GetInstance()->noRecoilSpread = (Settings::GetInstance()->noRecoilSpread) ? (false) : (true);
			Settings::GetInstance()->noRecoilSpreadSet = false;
			drawMenu();
		}

		// lockShootBot toggles
		if(GetAsyncKeyState(Settings::GetInstance()->lockShootBotToggle)) {
			Settings::GetInstance()->lockShootBot = (Settings::GetInstance()->lockShootBot) ? (false) : (true);
			target = 0;
			closestTarget = 0;
			CANO = 0;
			drawMenu();
		}

		if(GetAsyncKeyState(Settings::GetInstance()->lockShootBotboxToggle)) {
			Settings::GetInstance()->lockShootBotbox = (Settings::GetInstance()->lockShootBotbox == 0) ? (1) : (Settings::GetInstance()->lockShootBotbox == 1 ? (2) : (0));
			drawMenu();
		}

		// lockShootBot FOV
		if(GetAsyncKeyState(Settings::GetInstance()->lockShootBotFOVDown)) {
			Settings::GetInstance()->lockShootBotFOV = (Settings::GetInstance()->lockShootBotFOV > Settings::GetInstance()->lockShootBotFOVMin) ? (Settings::GetInstance()->lockShootBotFOV - 10) : (Settings::GetInstance()->lockShootBotFOVMin);
			drawMenu();
		} else if(GetAsyncKeyState(Settings::GetInstance()->lockShootBotFOVUp)) {
			Settings::GetInstance()->lockShootBotFOV = (Settings::GetInstance()->lockShootBotFOV < Settings::GetInstance()->lockShootBotFOVMax) ? (Settings::GetInstance()->lockShootBotFOV + 10) : (Settings::GetInstance()->lockShootBotFOVMax);
			drawMenu();
		}

		// lockShootBot speed
		if(GetAsyncKeyState(Settings::GetInstance()->lockShootBotSpeedDown)) {
			Settings::GetInstance()->lockShootBotSpeed = (Settings::GetInstance()->lockShootBotSpeed > Settings::GetInstance()->lockShootBotSpeedMin) ? (Settings::GetInstance()->lockShootBotSpeed - 1) : (Settings::GetInstance()->lockShootBotSpeedMin);
			drawMenu();
		} else if(GetAsyncKeyState(Settings::GetInstance()->lockShootBotSpeedUp)) {
			Settings::GetInstance()->lockShootBotSpeed = (Settings::GetInstance()->lockShootBotSpeed < Settings::GetInstance()->lockShootBotSpeedMax) ? (Settings::GetInstance()->lockShootBotSpeed + 1) : (Settings::GetInstance()->lockShootBotSpeedMax);
			drawMenu();
		}

		// Get Settings
		bool noRecoilSpread = Settings::GetInstance()->noRecoilSpread;
		bool noRecoilSpreadSet = Settings::GetInstance()->noRecoilSpreadSet;
		bool lockShootBot = Settings::GetInstance()->lockShootBot;
		bool esp = Settings::GetInstance()->esp;
		
		// Handle lockShootBot and ESP
		auto gameManager = Engine::GameManager::GetInstance();
		auto camera = Engine::GameRenderer::GetInstance()->GetCamera();
		auto gameInterface = Engine::Interface::GetInstance();

		if(gameInterface->IsInGame() && Engine::Memory::IsValidPtr(gameManager) && camera->IsInGame()) {
			if(lockShootBot & CANO !=0) {
				if(!GetAsyncKeyState(Settings::GetInstance()->lockShootBotKey)) {
					Settings::GetInstance()->wasButtonPressed = false;
					target = 0;
				}

				if(!target) {
					distance = Settings::GetInstance()->lockShootBotFOV;
				}

				Engine::Vector3 tTarget = (Settings::GetInstance()->lockShootBotbox == 0) ? (camera->WorldToScreen(target->GetChest())) : (Settings::GetInstance()->lockShootBotbox == 1 ? (camera->WorldToScreen(target->GetNeck())) : (camera->WorldToScreen(target->GetHead())));
				
				int tHealth = target->CAN();
				float boxX = tTarget.x - Settings::GetInstance()->crosshairX;
				float boxY = tTarget.y - Settings::GetInstance()->crosshairY;
				float tDistanceFromCrosshair = (float)sqrt((boxX * boxX) + (boxY * boxY));

				if(GetAsyncKeyState(Settings::GetInstance()->lockShootBotKey) && target && tHealth != 0 && tDistanceFromCrosshair <= Settings::GetInstance()->lockShootBotFOV && lockShootBot) {
					mouse_event(MOUSEEVENTF_MOVE, boxX * (Settings::GetInstance()->lockShootBotSpeed * 0.1), boxY * (Settings::GetInstance()->lockShootBotSpeed * 0.1), NULL, NULL);
				}
			}

			if(lockShootBot || esp || noRecoilSpread) {
				// Iterate through the entitylist for lockShootBot, esp, and no recoil/spread
				for(uint32_t i = 0; i < gameManager->GetEntities().GetSize(); i++) {
					Engine::Entity* entity = gameManager->GetEntities()[i];

				/*	if(entity == nullptr)
						return;
                 */
					if (!entity)
						return;
					// Allows us to rewrite both the ESP and no recoil/spread
					if(timer >= 100) {
						
						if(noRecoilSpread) {
							writeNoRecoilSpread = true;
							Settings::GetInstance()->noRecoilSpreadSet = false;
						}


						if (esp) {
							writeESP = true;
							Settings::GetInstance()->entitiesSet = 0;
						}

						timer = 0;
					}

					if(writeESP) {
						// Write the spotted variable to 12 entities in the list, this goes above the multiplayer entity count just in case
						if(Settings::GetInstance()->entitiesSet != 12) {
							entity->Shakira();
							Settings::GetInstance()->entitiesSet += 1;
						}
					}

					if(writeNoRecoilSpread && !noRecoilSpreadSet) {
						// Check if we are currently iterating over the local player
						if(camera->GetViewTranslation().Distance(entity->GetHead()) < 0.2f) {
							entity->PapaPerfectShot();
							Settings::GetInstance()->noRecoilSpreadSet = true;
						}
					}
					
					int eHealth = entity->CAN();
					if(eHealth > 0 && eHealth <= 200) {
						Engine::Vector3 eTarget = (Settings::GetInstance()->lockShootBotbox == 0) ? (camera->WorldToScreen(entity->GetChest())) : (Settings::GetInstance()->lockShootBotbox == 1 ? (camera->WorldToScreen(entity->GetNeck())) : (camera->WorldToScreen(entity->GetHead())));
					
						if(eTarget.z >= 1.0f) {
							float x = eTarget.x - Settings::GetInstance()->crosshairX;
							float y = eTarget.y - Settings::GetInstance()->crosshairY;
							float distanceFromCrosshair = (float)sqrt((x * x) + (y * y));
							
							if(distanceFromCrosshair <= Settings::GetInstance()->lockShootBotFOV) {
								if(distanceFromCrosshair <= distance) {
									distance = distanceFromCrosshair;
									closestTarget = entity;
								}
							}
						}
					}
				}
			}

			if(lockShootBot && CANO != 0) {
				// Lock onto player
				int eHealth = 0;
				if(closestTarget)
					eHealth = closestTarget->CAN();

				if(GetAsyncKeyState(Settings::GetInstance()->lockShootBotKey) && !Settings::GetInstance()->wasButtonPressed) {
					Settings::GetInstance()->wasButtonPressed = true;
					target = closestTarget;
				}

				if(GetAsyncKeyState(Settings::GetInstance()->lockShootBotKey) && Settings::GetInstance()->wasButtonPressed && eHealth == 0) {
					Settings::GetInstance()->wasButtonPressed = false;
				}
			}
		} else {
		if (CANO != 0)
			CANO = 0;

			if(target != 0)
				target = 0;

			if(closestTarget != 0)
				closestTarget = 0;

			if(Settings::GetInstance()->entitiesSet != 0)
				Settings::GetInstance()->entitiesSet = 0;

			if(Settings::GetInstance()->noRecoilSpreadSet)
				Settings::GetInstance()->noRecoilSpreadSet = false;
		}
		timer++;
		Sleep(10);
	}
}

void Main::Stop() {
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	FreeConsole();
}
