#pragma once

#include "mh2Types.h"

class CTexture {
public:

	Link m_lInDictionary;

	char m_name[32];
	
	union {

		char m_mask[32];
		
		struct {	// PC
			uint32 m_texObjFlags;
			IDirect3DTexture9* m_pTexObj;
		};
	};

	uint32 m_nWidth;
	uint32 m_nHeight;
	uint32 m_nDepth;
	uint32 m_nStride;
	uint32 m_flags;
	uint8  m_numMipLevels;
	uint8  m_swizzleMask;	// PS2 indexed textures only (PSMT8)

	union {

		struct {	// PS2, PSP
			uint8* m_pPixels;
			RGBA*  m_pPalette;
		};

		struct {	// PC
			void*  m_pTexture;		// DDS container (DXT1, DXT5 and RGBA only) 
			uint8  m_nRenderPass;	// 1 - opaque, 3 - transparent
			uint32 m_nTextureSize;
		};
	};
};

class CTexDictionary {
private:

	int32    m_numTextures;			// Unused
	LinkList m_texturesInDict;

public:

	int32 GetNumTextures();
	void ForAllTextures(CTexture* (*callback)(CTexture*, void*), void* data);

};