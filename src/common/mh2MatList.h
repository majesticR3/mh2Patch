#pragma once

#include "mh2Types.h"
#include "mh2TexDict.h"

class CMaterial {
public:

	union {
		CTexture* m_pTexture;
		char*     m_pTextureName;
	};

	bool m_bHasTexture;
	RGBA m_Color;
};

class CMaterialList {
public:

	CMaterial* m_pMaterials;
	uint32     m_numMaterials;
};