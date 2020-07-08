//技能管理

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
    void LoadAbilityInfo();     //加载技能配表信息，填充到m_vecAbilityInfo

private:
    std::vector<AbilityInfo*>              m_vecAbilityInfo;//技能配表信息
};



#endif