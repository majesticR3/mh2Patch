#pragma once

#include "mh2Types.h"
#include "mh2Frame.h"
#include "mh2Geometry.h"
#include "mh2AnimHier.h"

class CAtomic {
public:

	Link             m_inClumpLink;
	CFrame*          m_pParentFrame;
	CGeometry*       m_pGeometry;
	class CClump*    m_pClump;
	CAnimHierarchy*  m_pAnimHier;
	uint32           m_flags;
};

class CClump {
public:

	CFrame*                    m_pParentFrame;
	class CWorld*              m_pParentWorld;
	class CEntity*             m_pParentEntity;
	class CAnimBlendClumpData* m_pAnimData;
	CAnimHierarchy*            m_pAnimHier;
	LinkList                   m_atomicList;
};