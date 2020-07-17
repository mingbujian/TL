//���ܹ���

#ifndef TL_ABILITY_MGR_H
#define TL_ABILITY_MGR_H

#include"AbilityInfo.h"
#include<vector>

// Spell rank chain  (accessed using SpellMgr functions)
struct SpellChainNode
{
    AbilityInfo const* prev;
    AbilityInfo const* next;
    AbilityInfo const* first;
    AbilityInfo const* last;
    uint8  rank;
};

class AbilityMgr
{
public:
    void LoadAbilityInfo();     //���ؼ��������Ϣ����䵽m_vecAbilityInfo

private:
    std::vector<AbilityInfo*>              m_vecAbilityInfo;//���������Ϣ
};



#endif