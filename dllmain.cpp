
#include "pch.h"
#include "patch/mh2Patch.h"
#include "hook/MemoryMgr.h"

extern "C"
{
	__declspec(dllexport) void InitializeASI()
	{
		// Camera Y-Axis fix
		Memory::VP::Patch<float>(0x6CE0DC, 0.0f);
		Memory::VP::Patch<float>(0x6CE0E0, 0.0f);
		Memory::VP::Patch<float>(0x699188, MIN_CAMERA_PITCH);
		Memory::VP::Patch<float>(0x69918C, MAX_CAMERA_PITCH);
		Memory::VP::InjectHook(0x5B0510, &CPlayerEx::CalcCameraIdealPosition);

		// Blood decals fix
		Memory::VP::InjectHook(0x5AD857, &CPlayerEx::UpdateWiiExecution);
	}
}

