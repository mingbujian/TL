//������Ϣ����

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
    AbilityCategoryEntry const* CategoryEntry;  //����
    uint32 Dispel;                              //��������
    uint32 Attributes;                          //���ԣ�����
    uint64 Stances;                             //��̬
    uint32 Targets;                             //Ŀ�� ���Ŀ��ָ��ѡ��Ŀ��ʱ������Ӧ��Ŀ��
    uint32 TargetCreatureType;                  //Ŀ�괴��������
    uint32 RequiresSpellFocus;
    uint32 FacingCasterFlags;                   //ʩ���߱��
    uint32 CasterAuraState;                     //ʩ���⻷״̬
    uint32 TargetAuraState;                     //Ŀ��⻷״̬
    SpellCastTimeEntry const* CastTimeEntry;   //ʩ��ʱ��
    uint32 RecoveryTime;                        //cd���ָ�ʱ��
    uint32 CategoryRecoveryTime;                //
    uint32 StartRecoveryCategory;
    uint32 StartRecoveryTime;
    uint32 InterruptFlags;                      //��ϱ��
    uint32 AuraInterruptFlags;                  //�⻷��ϱ��
    uint32 ChannelInterruptFlags;               //������ϱ��
    uint32 ProcFlags;
    uint32 ProcChance;                          //�������� �ٷֱ� д30 ����30%
    uint32 ProcCharges;
    uint32 MaxLevel;
    uint32 BaseLevel;
    uint32 SpellLevel;
    SpellDurationEntry const* DurationEntry;            //����ʱ��
    SpellRangeEntry const* RangeEntry;                  //ʩ����Χ������
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
