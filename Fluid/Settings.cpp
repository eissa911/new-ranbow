#include "Settings.h"
#include <Windows.h>

Settings* Settings::instance;

Settings::Settings() {
	// Settings and Variables
	this->esp = false;

	this->entitiesSet = 0;

	this->noRecoilSpread = false;
	this->noRecoilSpreadSet = false;

	this->lockShootBot = false;
	this->wasButtonPressed = false;

	this->lockShootBotbox = 1;

	this->lockShootBotFOV = 90;

	this->lockShootBotSpeed = 3;

	this->width = GetSystemMetrics(SM_CXSCREEN);
	this->height = GetSystemMetrics(SM_CYSCREEN);

	this->crosshairX = width / 2;
	this->crosshairY = height / 2;

	// Keys
	this->espToggle = VK_F1;

	this->noRecoilSpreadToggle = VK_F2;

	this->lockShootBotToggle = VK_F3;

	this->lockShootBotboxToggle = VK_F4;

	this->lockShootBotFOVDown = VK_F5;
	this->lockShootBotFOVUp = VK_F6;

	this->lockShootBotSpeedDown = VK_F7;
	this->lockShootBotSpeedUp = VK_F8;

	this->lockShootBotKey = VK_RBUTTON;

	// Limits
	this->lockShootBotFOVMin = 30;
	this->lockShootBotFOVMax = 100;

	this->lockShootBotSpeedMin = 1;
	this->lockShootBotSpeedMax = 4;
}

Settings* Settings::GetInstance() {
	if(!instance)
		instance = new Settings();

	return instance;
}