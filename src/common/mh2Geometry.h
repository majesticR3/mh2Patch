#pragma once

#include "mh2Types.h"
#include "mh2MatList.h"
#include "mh2Skin.h"

class ALIGNED CGeometry {
public:

	CMaterialList m_matList;
	CSkin*        m_pSkin;
	uint32        __fieldC;
	uint32        m_nRefCount;
};