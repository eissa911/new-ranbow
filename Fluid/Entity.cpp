#include "Entity.h"
#include "Offsets.h"
#include "Memory.h"

namespace Engine {
	Vector3& Entity::GetFeet() {
		if(!Memory::IsValidPtr<Entity>(this))
			return *(new Vector3());

		return *Memory::Ptr<Vector3*>(this, OFFSET_Entity_FEET);
	}

	Vector3& Entity::GetLeftHand() {
		if(!Memory::IsValidPtr<Entity>(this))
			return *(new Vector3());

		return *Memory::Ptr<Vector3*>(this, OFFSET_Entity_LEFTHAND);
	}

	Vector3& Entity::GetRightHand() {
		if(!Memory::IsValidPtr<Entity>(this))
			return *(new Vector3());

		return *Memory::Ptr<Vector3*>(this, OFFSET_Entity_RIGHTHAND);
	}

	Vector3& Entity::GetChest() {
		if(!Memory::IsValidPtr<Entity>(this))
			return *(new Vector3());

		Vector3 chestPos;

		// Since there is no offset for the chest, we'll need to use some simple math to find it
		Vector3 feetPos = GetFeet();
		Vector3 leftHandPos = GetLeftHand(); // We can take either hand, we just want one of them
		Vector3 headPos = GetHead();

		chestPos.x = (feetPos.x + headPos.x) / 2.0;
		chestPos.y = (feetPos.y + headPos.y) / 2.0;
		chestPos.z = (leftHandPos.z + headPos.z) / 2.1; // I've tried using the feet position z coordinate, but I would always get the crotch level or head level no matter what

		return chestPos;
	}

	Vector3& Entity::GetNeck() {
		if(!Memory::IsValidPtr<Entity>(this))
			return *(new Vector3());

		return *Memory::Ptr<Vector3*>(this, OFFSET_Entity_NECK);
	}

	Vector3& Entity::GetHead() {
		if(!Memory::IsValidPtr<Entity>(this))
			return *(new Vector3());

		return *Memory::Ptr<Vector3*>(this, OFFSET_Entity_HEAD);
	}

	INT8 Entity::CAN() {
		if(!Memory::IsValidPtr<Entity>(this))
			return 0;

		auto canalma1 = *Memory::Ptr<void**>(this, OFFSET_Entity_EntityINFO);

		auto canalma2 = *Memory::Ptr<void**>(canalma1, OFFSET_EntityINFO_MainComponet);

		auto canalma3 = *Memory::Ptr<void**>(canalma2, OFFSET_MainComponet_CHILDCOMPONENT);

		return *Memory::Ptr<INT8*>(canalma3, OFFSET_CHILDCOMPONENT_HEALTH);
	}

	INT8 Entity::GetTeam() {
		if(!Memory::IsValidPtr(this))
			return -1;

		auto playerInfo = *Memory::Ptr<void**>(this, OFFSET_Entity_PlayerInfo);

		auto playerMainComponent = *Memory::Ptr<void**>(playerInfo, OFFSET_PlayerInfo_MainComponet);

		return *Memory::Ptr<INT8*>(playerMainComponent, OFFSET_MainComponet_TEAMID);

		// TEAM ID OFFSET IS NOT TOWARDS A POINTER, ITS THE STRAIGHT VALUE
	}

	void Entity::Shakira() {
		if(!Memory::IsValidPtr(this))
			return;

		auto shitstorm1 = *Memory::Ptr<void**>(this, OFFSET_Entity_EntityINFO);
		if(!Memory::IsValidPtr(shitstorm1))
			return;

		auto shitstorm2 = *Memory::Ptr<void**>(shitstorm1, OFFSET_EntityINFO_MainComponet);
		if(!Memory::IsValidPtr(shitstorm2))
			return;

		auto shitstorm3 = *Memory::Ptr<void**>(shitstorm2, ORACLE_1);
		if(!Memory::IsValidPtr(shitstorm3))
			return;

		auto shitstorm4 = *Memory::Ptr<void**>(shitstorm3, ORACLE_2);
		if(!Memory::IsValidPtr(shitstorm4))
			return;

		int* shitstorm5 = Memory::Ptr<int*>(shitstorm4, ORACLE_3);

		*shitstorm5 = 1;
	}


	void Entity::PapaPerfectShot() {
		if(!Memory::IsValidPtr(this))
			return;

		auto akc1 = *Memory::Ptr<void**>(this, OFFSET_Entity_EntityINFO);
		if(!Memory::IsValidPtr(akc1))
			return;

		auto akc2 = *Memory::Ptr<void**>(akc1, OFFSET_EntityINFO_MainComponet);
		if(!Memory::IsValidPtr(akc2))
			return;

		auto akc3 = *Memory::Ptr<void**>(akc2, OFFSET_MainComponet_WEAPONCOMPONENT);
		if(!Memory::IsValidPtr(akc3))
			return;

		auto akc4 = *Memory::Ptr<void**>(akc3, OFFSET_WEAPONCOMPONENT_WEAPONPROCESSOR);
		if(!Memory::IsValidPtr(akc4))
			return;

		auto akc5 = *Memory::Ptr<void**>(akc4, OFFSET_WEAPONPROCESSOR_WEAPON);
		if(!Memory::IsValidPtr(akc5))
			return;

		auto akc6 = *Memory::Ptr<void**>(akc5, OFFSET_WEAPON_WEAPONINFO1);
		if(!Memory::IsValidPtr(akc6))
			return;

		auto akc7 = *Memory::Ptr<void**>(akc6, OFFSET_WEAPON_WEAPONINFO2);
		if (!Memory::IsValidPtr(akc7))
			return;

		// Start getting recoil and spread from WeaponInfo
		//float* recep = Memory::Ptr<float*>(akc7, OFFSET_WEAPONINFO_RECOIL);
		//float* serap = Memory::Ptr<float*>(akc7, OFFSET_WEAPONINFO_SPREAD);

		// Set recoil and spread
		//*recep = 0.0f;
		//*serap = 0.0f;
	} 
}