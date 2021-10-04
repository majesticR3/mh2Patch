#include "pch.h"
#include "mh2Wrappers.h"

AssignGlobalVar(float, CGameTime::ms_timeStepSecs, 0x6ECE68);

AssignGlobalVar(bool, CCamera::ms_bUnknownLockCameraSwitch, 0x789819);

AssignGlobalVar(int32, CCamGlobals::m_nUpdateType, 0x76F244);
AssignGlobalVar(int32, CCamGlobals::m_nUpdateFramesLeft, 0x76F24C);
AssignGlobalVar(CVector, CCamGlobals::m_vecCurLookBackPos1, 0x76F820);
AssignGlobalVar(CVector, CCamGlobals::m_vecCurLookBackPos2, 0x76F830);
AssignGlobalVar(CVector, CCamGlobals::m_vecCurLookAtPos, 0x76F840);
AssignGlobalVar(bool, CCamGlobals::m_bCamSwitchHack, 0x76F4FD);
AssignGlobalVar(bool, CCamGlobals::m_bCamSwitchHack2, 0x76F4FE);