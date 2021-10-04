#pragma once

#include "mh2Types.h"
#include "mh2Matrix.h"
#include "mh2AnimHier.h"

class ALIGNED CFrame {
public:

	void*           m_pReserved;	// Ptr placeholder for frame pool allocator
	
	CFrame*         m_pNext;
	CFrame*         m_pParent;
	CFrame*         m_pRoot;
	CFrame*         m_pChild;
	
	CAnimHierarchy* m_pAnimHier;

	char            m_name[32];

	bool            m_bDirty;

	CMatrix         m_localMatrix;
	CMatrix         m_worldMatrix;
};

