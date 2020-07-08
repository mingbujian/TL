#pragma once
#include<unordered_map>
#include"Define.h""

#define PLAYER_MAX_SKILLS           127

enum SkillUpdateState
{
	SKILL_UNCHANGED = 0,
	SKILL_CHANGED = 1,
	SKILL_NEW = 2,
	SKILL_DELETED = 3
};

struct SkillStatusData
{
	SkillStatusData(uint8 _pos, SkillUpdateState _uState) : pos(_pos), uState(_uState)
	{
	}
	uint8 pos;
	SkillUpdateState uState;
};
enum PlayerSpellState
{
    PLAYERSPELL_UNCHANGED = 0,
    PLAYERSPELL_CHANGED = 1,
    PLAYERSPELL_NEW = 2,
    PLAYERSPELL_REMOVED = 3,
    PLAYERSPELL_TEMPORARY = 4
};

struct PlayerSpell
{
    PlayerSpellState state : 8;
    bool active : 1;                             // show in spellbook
    bool dependent : 1;                             // learned as result another spell learn, skill grow, quest reward, etc
    bool disabled : 1;                             // first rank has been learned in result talent learn but currently talent unlearned, save max learned ranks
};

typedef std::unordered_map<uint32, PlayerSpell*> PlayerSpellMap;
typedef std::unordered_map<uint32, SkillStatusData> SkillStatusMap;

class Player
{
public:
	void SetSkill(uint16 id, uint16 step, uint16 newVal, uint16 maxVal);
	uint16 GetMaxSkillValue(uint32 skill) const;        // max + perm. bonus + temp bonus
	uint16 GetPureMaxSkillValue(uint32 skill) const;    // max
	uint16 GetSkillValue(uint32 skill) const;           // skill value + perm. bonus + temp bonus
	uint16 GetBaseSkillValue(uint32 skill) const;       // skill value + perm. bonus
	uint16 GetPureSkillValue(uint32 skill) const;       // skill value
	int16 GetSkillPermBonusValue(uint32 skill) const;
	int16 GetSkillTempBonusValue(uint32 skill) const;
	uint16 GetSkillStep(uint16 skill) const;            // 0...6
	bool HasSkill(uint32 skill) const;
	void LearnSkillRewardedSpells(uint32 skillId, uint32 skillValue);


    bool AddSpell(uint32 spellId, bool active, bool learning, bool dependent, bool disabled, bool loading = false, uint32 fromSkill = 0);
    void LearnSpell(uint32 spell_id, bool dependent, uint32 fromSkill = 0);
    void RemoveSpell(uint32 spell_id, bool disabled = false, bool learn_low_rank = true);
    void ResetSpells(bool myClassOnly = false);


    PlayerSpellMap const& GetSpellMap() const { return m_spells; }
    PlayerSpellMap      & GetSpellMap() { return m_spells; }

    //void AddSpellMod(SpellModifier* mod, bool apply);
    //static bool IsAffectedBySpellmod(SpellInfo const* spellInfo, SpellModifier* mod, Spell* spell = nullptr);
    //template <class T>
    //void ApplySpellMod(uint32 spellId, SpellModOp op, T& basevalue, Spell* spell = nullptr) const;
    //static void ApplyModToSpell(SpellModifier* mod, Spell* spell);
    //void SetSpellModTakingSpell(Spell* spell, bool apply);

private:
	SkillStatusMap mSkillStatus;
    PlayerSpellMap m_spells;
};