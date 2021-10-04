#pragma once

#include "mh2Types.h"
#include "mh2Vector.h"
#include "mh2Matrix.h"
#include "mh2AnimBlendAssociation.h"

#define GetValuePtr(_type, _ptr, _offset) \
	(reinterpret_cast<_type*>(reinterpret_cast<uint8*>(_ptr) + _offset))

#define GetValue(_type, _ptr, _offset) \
	(*GetValuePtr(_type, _ptr, _offset))

#define GetFieldPtr(_type, _offset) \
	(reinterpret_cast<_type*>(reinterpret_cast<uint8*>(this) + _offset))

#define GetField(_type, _offset) \
	(*GetFieldPtr(_type, _offset))

#define AssignField(_type, _name, _offset) \
	_type& _name = *GetFieldPtr(_type, _offset)

#define AssignGlobalVar(_type, _name, _addr) \
	_type& _name = *reinterpret_cast<_type*>(_addr)

class CEntity {};

class COddEntity : public CEntity {};

class CCollectable : public COddEntity {
public:

};

class CWeaponCollectable : public CCollectable {
public:

    inline int32 GetExecuteAnimClass() {
        return reinterpret_cast<int32(__thiscall*)(CWeaponCollectable*)>
            (0x527320)(this);
    }
};

class CCharacter : public CEntity {
public:

    inline CWeaponCollectable* GetUsedCollectable() {
        return reinterpret_cast<CWeaponCollectable* (__thiscall*)(CCharacter*)>
            (0x4F66C0)(this);
    }
};

class CPed : public CCharacter {
public:

    enum ExecutionType {
        EXECUTION_NONE,
        EXECUTION_HASTY,
        EXECUTION_VIOLENT,
        EXECUTION_GRUESOME,
        EXECUTION_ENVIRONMENTAL,
        EXECUTION_JUMP
    };

    inline bool isCrawling() {
        return reinterpret_cast<bool(__thiscall*)(CPed*)>
            (0x42E11D)(this);
    }
};

class CAutoPed : public CPed {
public:

};

class CPlayer : public CAutoPed {
public:

    enum RedExecutionType {
        RED_EXEC_NORMAL,
        RED_EXEC_ENVIRONMENTAL,
        RED_EXEC_JUMP
    };

	inline bool IAmSniping() {
		return reinterpret_cast<bool(*)()>(0x598150)();
	}

    inline void GetPlayerRootOffsetForCameraPositioning(CVector* pos,
        CMatrix* rot, int32 flags) {
        reinterpret_cast<void(__thiscall*)(CPlayer*, CVector*, CMatrix*, int32)>
            (0x5AF950)(this, pos, rot, flags);
    }

    inline int32 GetExecuteStage() {
        return reinterpret_cast<uint32(__thiscall*)(CPlayer*)>(0x599840)(this);
    }

    inline void UpdateWiiExecution() {
        reinterpret_cast<void(__thiscall*)(CPlayer*)>(0x5A9640)(this);
    }
};

class CPedBodyAnimFSM {
public:
    inline CAnimBlendAssociation* GetAnimAssociation() {
        return reinterpret_cast<CAnimBlendAssociation * (__thiscall*)(void*)>
            (0x42E050)(this);
    }
};

class CharacterDamageManager {
public:

    inline void AddDecal(CEntity* entity, float posX, float posY,
        char const* textureName, uint32 flags) {
        reinterpret_cast<void(__thiscall*)(CharacterDamageManager*, CEntity*,
            float, float, char const*, uint32)>
            (0x5B9270)(this, entity, posX, posY, textureName, flags);
    }

    inline static CharacterDamageManager* GetInstance() {
        return reinterpret_cast<CharacterDamageManager * (*)()>(0x5B8D00)();
    }
};

class CGameTime {
public:

    static float& ms_timeStepSecs;
};

class CCamera {
public:

    static bool& ms_bUnknownLockCameraSwitch;

};

class CCamGlobals {
public:
    static int32& m_nUpdateType;
    static int32& m_nUpdateFramesLeft;

    static CVector& m_vecCurLookBackPos1;
    static CVector& m_vecCurLookBackPos2;
    static CVector& m_vecCurLookAtPos;

    static bool& m_bCamSwitchHack;
    static bool& m_bCamSwitchHack2;
};

class CMhGlobalData {
public:

    static inline bool InteractiveExecModeOn() {
        return GetValue(uint32, *(void**)0x7604B0, 0xF0) != 0;
    }
};
