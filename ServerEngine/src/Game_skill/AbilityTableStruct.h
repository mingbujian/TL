//技能表相关的结果定义

#ifndef TL_ABILITY_TABLE_STRUCT_H
#define TL_ABILITY_TABLE_STRUCT_H

#include "Define.h"

#define MAX_SPELL_EFFECTS 3
#define MAX_SPELL_REAGENTS 8

struct AbilityCategoryEntry
{
    uint32 Id;
    uint32 Flags;
};

struct SpellCastTimeEntry
{
    uint32    ID;                                           // 0
    int32     CastTime;                                     // 1
};

struct SpellDurationEntry
{
    uint32    ID;
    int32     Duration[3];
};

struct SpellRangeEntry
{
    uint32    ID;
    float     minRangeHostile;
    float     minRangeFriend;
    float     maxRangeHostile;
    float     maxRangeFriend;
    uint32    type;
    //char*     Name[16];                                   // 7-23 unused
                                                            // 24 string flags, unused
    //char*     Name2[16];                                  // 25-40 unused
                                                            // 41 string flags, unused
};
#endif