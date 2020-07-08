#ifndef TL_OBJECT_H
#define TL_OBJECT_H
class Player;
class Spell;
class SpellCastTargets;
class SpellInfo;

class Object
{
public:
    Player* GetSpellModOwner() const;
    int32 CalculateSpellDamage(SpellInfo const* spellInfo, uint8 effIndex, int32 const* basePoints = nullptr) const;

    // CastSpell's third arg can be a variety of things - check out CastSpellExtraArgs' constructors!
    void CastSpell(SpellCastTargets const& targets, uint32 spellId, CastSpellExtraArgs const& args = { });
    void CastSpell(WorldObject* target, uint32 spellId, CastSpellExtraArgs const& args = { });
    void CastSpell(Position const& dest, uint32 spellId, CastSpellExtraArgs const& args = { });
};

#endif // 
