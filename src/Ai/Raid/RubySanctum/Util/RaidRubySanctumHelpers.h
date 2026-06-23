#ifndef _PLAYERBOT_RAIDRUBYSANCTUMHELPERS_H
#define _PLAYERBOT_RAIDRUBYSANCTUMHELPERS_H

#include <cstdint>

namespace RubySanctumHelpers
{
constexpr uint32 RS_MAP_ID = 724;

enum RubySanctumNpcs : uint32
{
    NPC_ONYX_FLAMECALLER       = 39814,
    NPC_METEOR_STRIKE_FLAME    = 40055,
};

enum RubySanctumSpells : uint32
{
    SPELL_BLADE_TEMPEST        = 75125,
    SPELL_CONFLAGRATION        = 74452,
    SPELL_FLAME_BEACON         = 74453,
    SPELL_FIERY_COMBUSTION     = 74562,
    SPELL_SOUL_CONSUMPTION     = 74792,
};
}

#endif
