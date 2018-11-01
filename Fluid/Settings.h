#pragma once

class Settings {
public:
	// Settings and Variables
	bool IsValid;
	bool esp;

	int entitiesSet;

	bool noRecoilSpread;
	bool noRecoilSpreadSet;

	bool lockShootBot;
	bool wasButtonPressed;

	int lockShootBotbox;

	int lockShootBotFOV;

	int lockShootBotSpeed;

	int width;
	int height;

	int crosshairX;
	int crosshairY;

	// Keys
	int espToggle;

	int noRecoilSpreadToggle;

	int lockShootBotToggle;

	int lockShootBotboxToggle;

	int lockShootBotFOVDown;
	int lockShootBotFOVUp;

	int lockShootBotSpeedDown;
	int lockShootBotSpeedUp;

	int lockShootBotKey;

	// Limits
	int lockShootBotFOVMin;
	int lockShootBotFOVMax;

	int lockShootBotSpeedMin;
	int lockShootBotSpeedMax;

	static Settings* GetInstance();

private:
	Settings();

	static Settings* instance;
};