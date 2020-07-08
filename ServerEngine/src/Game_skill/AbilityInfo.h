//技能信息管理

#ifndef TL_ABILITY_INFO_H
#define TL_ABILITY_INFO_H

#include "AbilityTableStruct.h"
#include "AbilityEffectInfo.h"
#include "Define.h"

enum SpellEffects
{

};
enum AuraType : uint32
{

};
// Spell clasification
enum SpellSpecificType
{
    SPELL_SPECIFIC_NORMAL = 0,
    SPELL_SPECIFIC_SEAL = 1,
    SPELL_SPECIFIC_AURA = 3,
};

// Spell aura states
enum AuraStateType
{   // (C) used in caster aura state     (T) used in target aura state
    // (c) used in caster aura state-not (t) used in target aura state-not
    AURA_STATE_NONE = 0,            // C   |
    AURA_STATE_DEFENSE = 1,            // C   |
    AURA_STATE_HEALTHLESS_20_PERCENT = 2,            // CcT |
    AURA_STATE_BERSERKING = 3,            // C T |
    AURA_STATE_FROZEN = 4,            //  c t| frozen target
    AURA_STATE_JUDGEMENT = 5,            // C   |
};

class AbilityInfo
{
    friend class AbilityMgr;
public:
    uint32 Id;                                  //id
    AbilityCategoryEntry const* CategoryEntry;  //分类
    uint32 Dispel;                              //消除类型
    uint32 Attributes;                          //属性，特征
    uint64 Stances;                             //姿态
    uint32 Targets;                             //目标 这个目标指无选定目标时，所对应的目标
    uint32 TargetCreatureType;                  //目标创生体类型
    uint32 RequiresSpellFocus;
    uint32 FacingCasterFlags;                   //施法者标记
    uint32 CasterAuraState;                     //施法光环状态
    uint32 TargetAuraState;                     //目标光环状态
    SpellCastTimeEntry const* CastTimeEntry;   //施法时间
    uint32 RecoveryTime;                        //cd，恢复时间
    uint32 CategoryRecoveryTime;                //
    uint32 StartRecoveryCategory;
    uint32 StartRecoveryTime;
    uint32 InterruptFlags;                      //打断标记
    uint32 AuraInterruptFlags;                  //光环打断标记
    uint32 ChannelInterruptFlags;               //引导打断标记
    uint32 ProcFlags;
    uint32 ProcChance;                          //发动几率 百分比 写30 就是30%
    uint32 ProcCharges;
    uint32 MaxLevel;
    uint32 BaseLevel;
    uint32 SpellLevel;
    SpellDurationEntry const* DurationEntry;            //持续时间
    SpellRangeEntry const* RangeEntry;                  //施法范围，距离
    float  Speed;
    uint32 StackAmount;
    int32  Reagent[MAX_SPELL_REAGENTS];
    uint32 ReagentCount[MAX_SPELL_REAGENTS];
    int32  EquippedItemClass;
    int32  EquippedItemSubClassMask;
    int32  EquippedItemInventoryTypeMask;
    uint32 Priority;
    uint32 MaxTargetLevel;
    uint32 MaxAffectedTargets;
    uint32 DmgClass;
    uint32 PreventionType;
    int32  AreaGroupId;
    uint32 SchoolMask;
    SpellEffectInfo Effects[MAX_SPELL_EFFECTS];
    uint32 ExplicitTargetMask;
    SpellChainNode const* ChainEntry;
public:
    AbilityInfo();
    ~AbilityInfo();


    uint32 GetCategory() const;
    bool HasEffect(SpellEffects effect) const;
    bool HasAura(AuraType aura) const;
    bool HasAreaAuraEffect() const;
    bool HasOnlyDamageEffects() const;
private:
    SpellSpecificType _spellSpecific;
    AuraStateType _auraState;

};

#endif // 
