#include "pch.h"
#include "mh2Patch.h"

void CPlayerEx::CalcCameraIdealPosition(CVector* cameraPos, CVector* playerPos,
	CMatrix* cameraMatrix, CMatrix* playerMatrix, CVector* outCameraPos)
{
	AssignField(CVector2D, m_vecCameraMoveDir, 1184);
	AssignField(CClump*, m_pClump, 184);

	AssignField(int32, m_nLookBackState, 1232);
	AssignField(int32, m_nMovementType, 956);
	AssignField(int32, m_nWeaponType, 968);
	AssignField(float, m_fCameraPitch, 4400);
	AssignField(CPed*, m_pLockedOnPed, 4500);

	// Process custom camera pitch angle
	static float fCustomCameraPitch = m_fCameraPitch;

	fCustomCameraPitch += m_vecCameraMoveDir.y * 
		CGameTime::ms_timeStepSecs * 30.0f;

	if (fCustomCameraPitch > MAX_CAMERA_PITCH)
		fCustomCameraPitch = MAX_CAMERA_PITCH;
	else if (fCustomCameraPitch < MIN_CAMERA_PITCH)
		fCustomCameraPitch = MIN_CAMERA_PITCH;

	// Find camera pos offset vector
	CVector camPosOffset;
	GetPlayerRootOffsetForCameraPositioning(playerPos, playerMatrix, 0);

	if (!CCamera::ms_bUnknownLockCameraSwitch && m_nLookBackState) {
		
		CCamGlobals::m_nUpdateType = 0; 
		CCamGlobals::m_nUpdateFramesLeft = 0;

		if (CCamGlobals::m_bCamSwitchHack && CCamGlobals::m_bCamSwitchHack2)
			camPosOffset = CCamGlobals::m_vecCurLookBackPos1;
		else {
			CCamGlobals::m_bCamSwitchHack = true;
			camPosOffset = CCamGlobals::m_vecCurLookBackPos2;
		}
	} else if (m_nMovementType == MOVEMENT_CRAWL || 
		(m_nMovementType == MOVEMENT_AIM && isCrawling())) {

		CVector const* pClumpPos = 
			m_pClump->m_pParentFrame->m_localMatrix.GetPos();

		camPosOffset.x = 0.0f;
		camPosOffset.y = sinf((pClumpPos->x + pClumpPos->z) * 4.0f);
		camPosOffset.y = fabsf(camPosOffset.y / 20.0f);
		camPosOffset.z = -0.001f;

	} else
		camPosOffset = CCamGlobals::m_vecCurLookBackPos2;

	// Sync original and custom camera angle
	if (m_nMovementType == MOVEMENT_CLIMBABLE_MOUNT ||
		m_pLockedOnPed || IAmSniping()) {

		fCustomCameraPitch = m_fCameraPitch;

	} else {

		CCamGlobals::m_vecCurLookAtPos = CVector::ms_zero;

		if (m_nWeaponType != WEAPON_TYPE_LURE && !IAmSniping())
			ApplyCameraRecoil(fCustomCameraPitch);

		m_fCameraPitch = fCustomCameraPitch;
	}

	// Calc global camera pos
	CMatrix camPitchMatrix;
	camPitchMatrix.SetRotation(CVector::ms_xAxis, fCustomCameraPitch);

	camPosOffset.FastTransformVector(&camPosOffset, &camPitchMatrix);
	camPosOffset.FastTransformVector(&camPosOffset, playerMatrix);

	outCameraPos->FastSum(playerPos, &camPosOffset);
}

void CPlayerEx::ApplyCameraRecoil(float& pitch)
{
	AssignField(CVector2D, m_vecRecoilDist, 4712);
	AssignField(float, m_fCameraPitch, 4400);
	AssignField(float, m_fRecoilTime, 4704);
	AssignField(float, m_fRecoilTimeLeft, 4708);

	if (m_fRecoilTimeLeft > 0.0f) {

		float recoilCurr = sinf(DegToRad(90.0f * (1.0f -
			m_fRecoilTimeLeft / m_fRecoilTime)));

		float recoilNext = sinf(DegToRad(90.0f * (1.0f -
			(m_fRecoilTimeLeft - CGameTime::ms_timeStepSecs) / m_fRecoilTime)));

		float recoilAmount;

		if (recoilNext < 0.5f)
			recoilAmount = recoilNext - recoilCurr;
		else if (recoilCurr >= 0.5f)
			recoilAmount = recoilCurr - recoilNext;
		else
			recoilAmount = 1.0f - recoilCurr - recoilNext;

		pitch += recoilAmount * m_vecRecoilDist.x;
	}
}

void CPlayerEx::UpdateWiiExecution()
{
	AssignField(CPedBodyAnimFSM*, m_pBodyAnimFSM, 700);

	AssignField(uint32, m_numDecalsSplatter, 4436);
	AssignField(uint32, m_numDecalsVictim, 4432);
	AssignField(CPed*, m_pExecuteVictim, 4420);

	AssignField(uint32, m_nSpecialExecType, 4472);
	AssignField(uint32, m_nExecutingStage, 4372);
	AssignField(bool, m_bIsExecuting, 4358);

	if (CMhGlobalData::InteractiveExecModeOn()) {
		CPlayer::UpdateWiiExecution();
		return;
	}

	CWiiExecutionMap* pExecMap = CWiiExecutionMap::GetInstance();

	CharacterDamageManager* pCharDamage =
		CharacterDamageManager::GetInstance();

	// Find execution anim class id
	int32 execId;

	void* pEnvExecutor = GetValue(void*, m_pExecuteVictim, 4160);

	if (pEnvExecutor) {
		execId = GetValue(int32, pEnvExecutor, 444) +
			EXEC_ANIM_ENVIRONMENTAL_LIQUID_NITROGEN;
	} else
		execId = GetUsedCollectable()->GetExecuteAnimClass();

	if (execId >= EXEC_UNDEFINED)
		return;

	// Find execution stage
	int32 execStage = GetExecuteStage();

	if (m_bIsExecuting)
		execStage = m_nExecutingStage;

	if (m_nSpecialExecType == RED_EXEC_JUMP)
		execStage = EXEC_STAGE_JUMP;

	if (execStage > EXEC_STAGE_JUMP)
		return;

	// Add decals
	CAnimBlendAssociation* pAnimAssoc = m_pBodyAnimFSM->GetAnimAssociation();

	uint32 numDecals;
	CExecutionDecal* pDecal;

	numDecals = pExecMap->m_aVictimDecalsCount[execId][execStage];
	pDecal = &pExecMap->m_aVictimDecals[execId][execStage][m_numDecalsVictim];

	for (uint32 i = m_numDecalsVictim; i < numDecals; ++i) {
		if (pDecal->m_fTime > pAnimAssoc->m_fCurrentTime)
			break;

		pCharDamage->AddDecal(m_pExecuteVictim, pDecal->m_fPosX, pDecal->m_fPosY,
			pDecal->m_TextureName, 0);

		++m_numDecalsVictim;
		++pDecal;
	}

	numDecals = pExecMap->m_aSplatterDecalsCount[execId][execStage];
	pDecal = &pExecMap->m_aSplatterDecals[execId][execStage][m_numDecalsSplatter];

	for (uint32 i = m_numDecalsSplatter; i < numDecals; ++i) {
		if (pDecal->m_fTime > pAnimAssoc->m_fCurrentTime)
			break;

		pCharDamage->AddDecal(this, pDecal->m_fPosX, pDecal->m_fPosY,
			pDecal->m_TextureName, 0);

		++m_numDecalsSplatter;
		++pDecal;
	}
}
