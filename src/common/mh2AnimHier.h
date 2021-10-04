#pragma once

#include "mh2Types.h"
#include "mh2Quaternion.h"
#include "mh2Matrix.h"

class CAnimNodeInfo {
public:

    int16         m_BoneID;
    int16         m_Flags;
    class CFrame* m_pFrame;
};

class CAnimKeyFrame {
public:

    CQuaternion m_qtnRotation;
    CVector     m_vecTranslation;
};

class CAnimHierarchy {
public:

    int32          m_numNodes;
    bool           m_bUpdateLtms;
    class CFrame*  m_pParentFrame;
    CAnimNodeInfo* m_pNodeInfo;
    CAnimKeyFrame* m_pKeyFrameArray;
    CMatrix*       m_pMatrixArray;
};
