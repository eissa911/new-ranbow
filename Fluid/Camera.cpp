#include "Camera.h"
#include "Offsets.h"
#include "Memory.h"
#include <Math.h>
#include "Settings.h"
#include <iostream>


namespace Engine {
	Vector3& Camera::GetViewRight() {
		if(!Memory::IsValidPtr<Camera>(this))
			return *(new Vector3());

		return *Memory::Ptr<Vector3*>(this, OFFSET_Camera_VIEWRIGHT);
	}

	Vector3& Camera::GetViewUp() {
		if(!Memory::IsValidPtr<Camera>(this))
			return *(new Vector3());

		return *Memory::Ptr<Vector3*>(this, OFFSET_Camera_VIEWUP);
	}

	Vector3& Camera::GetViewForward() {
		if(!Memory::IsValidPtr<Camera>(this))
			return *(new Vector3());

		return *Memory::Ptr<Vector3*>(this, OFFSET_Camera_VIEWFORWARD);
	}

	Vector3& Camera::GetViewTranslation() {
		if(!Memory::IsValidPtr<Camera>(this))
			return *(new Vector3());

		return *Memory::Ptr<Vector3*>(this, OFFSET_Camera_VIEWTRANSLATION);
	}

	float Camera::GetViewFovX() {
		if(!Memory::IsValidPtr<Camera>(this))
			return 0.0f;

		return *Memory::Ptr<float*>(this, OFFSET_Camera_VIEWFOVX);
	}

	float Camera::GetViewFovY() {
		if(!Memory::IsValidPtr<Camera>(this))
			return 0.0f;

		return *Memory::Ptr<float*>(this, OFFSET_Camera_VIEWFOVY);
	}

	bool Camera::IsInGame() {
		if(!Memory::IsValidPtr(this))
			return false;

		Vector3 vt = GetViewTranslation();

		if(vt.x == 0.0f && vt.y == 0.0f && vt.z == 0.0f)
			return false;

		float fovX = GetViewFovX();
		float fovY = GetViewFovY();

		if(fovX == 0.0f && fovY == 0.0f)
			return false;

		return true;
	}

	Vector3 Camera::WorldToScreen(Vector3& position) {
		if(!Memory::IsValidPtr<Camera>(this))
			return *(new Vector3());

		Vector3 temp = position - GetViewTranslation();

		float x = temp.Dot(GetViewRight());
		float y = temp.Dot(GetViewUp());
		float z = temp.Dot(GetViewForward() * -1);

		return *(new Vector3((Settings::GetInstance()->width / 2) * (1 + x / GetViewFovX() / z), (Settings::GetInstance()->height / 2) * (1 - y / GetViewFovY() / z), z));
	}
}