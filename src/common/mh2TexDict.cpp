#include "pch.h"
#include "mh2TexDict.h"

int32 CTexDictionary::GetNumTextures()
{
	m_numTextures = 0;

	Link* link = m_texturesInDict.next;
	while (link != &m_texturesInDict) {

		link = link->next;
		++m_numTextures;
	}

	return m_numTextures;
}

void CTexDictionary::ForAllTextures(CTexture* (*callback)(CTexture*, void*), void* data)
{
	Link* link = m_texturesInDict.next;
	while (link!=&m_texturesInDict) {

		CTexture* texture = LinkGetData(link, CTexture, m_lInDictionary);
		link = link->next;

		if (!callback(texture, data))
			break;
	}
}
