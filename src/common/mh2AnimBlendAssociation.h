#pragma once

#include "mh2Types.h"

class CAnimBlendNode;
class CAnimBlendHierarchy;

class CAnimBlendAssociation {
private:
    void*                vfTable;

public:
    Link                 m_inClumpDataLink;
    CAnimBlendNode*      m_pNodeArray;
    CAnimBlendHierarchy* m_pAnimHier;
    float                __float14;
    float                m_fBlendAmount;
    float                __float1C;
    float                m_fCurrentTime;
    uint8                __gap24[4];
    float                m_fSpeed;
    int16                m_numNodes;
    uint16               m_flags;
    float                __float30;

    CAnimBlendAssociation* (*m_pFinishCallBack)(CAnimBlendAssociation*, void*);
    void*                  m_pFinishCallBackData;

    uint32               m_numActiveSFXEvents;
};