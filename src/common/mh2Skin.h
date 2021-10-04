#pragma once

#include "mh2Types.h"
#include "mh2Matrix.h"

class CSkin {
public:

	uint32   m_numNodes;
	CMatrix* m_pInverseMatrices;
};