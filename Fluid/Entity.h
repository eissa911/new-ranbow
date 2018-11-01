#pragma once

#include "Vector3.h"
#include <windows.h>

namespace Engine {
	class Entity {
	public:
		Vector3& GetFeet();
		Vector3& GetLeftHand();
		Vector3& GetRightHand();
		Vector3& GetChest();
		Vector3& GetNeck();
		Vector3& GetHead();
		INT8 CAN();
		INT8 GetTeam();
		void Shakira();
		void PapaPerfectShot();
	};
}