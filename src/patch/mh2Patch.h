#pragma once

#include "mh2AnimBlendAssociation.h"
#include "mh2ExecutionMap.h"

#include "mh2SharedEnums.h"
#include "mh2Wrappers.h"

#include "mh2Vector.h"
#include "mh2Matrix.h"
#include "mh2Clump.h"

// Camera settings
constexpr float MIN_CAMERA_PITCH = -50.0f;
constexpr float MAX_CAMERA_PITCH = 60.0f;

class CPlayerEx : public CPlayer {
public:

	void CalcCameraIdealPosition(CVector* cameraPos, CVector* playerPos,
		CMatrix* cameraMatrix, CMatrix* playerMatrix, CVector* outCameraPos);

	void ApplyCameraRecoil(float &pitch);
	void UpdateWiiExecution();
};