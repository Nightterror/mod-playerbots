#ifndef _PLAYERBOT_RAIDSUNWELLHELPERS_H
#define _PLAYERBOT_RAIDSUNWELLHELPERS_H

#include "PlayerbotAI.h"
#include "Playerbots.h"

#include <cstdint>

namespace SunwellHelpers
{
constexpr uint32 SUNWELL_MAP_ID = 580;

enum SunwellNpcs : uint32
{
    NPC_BRUTALLUS                = 24882,
    NPC_FELMYST                  = 25038,
    NPC_DEMONIC_VAPOR            = 25265,
    NPC_UNYIELDING_DEAD          = 25268,
    NPC_LADY_SACROLASH           = 25165,
    NPC_GRAND_WARLOCK_ALYTHESS   = 25166,
    NPC_SHADOW_IMAGE             = 25214,
    NPC_MURU                     = 25741,
    NPC_ENTROPIUS                = 25840,
    NPC_DARK_FIEND               = 25744,
    NPC_VOID_SENTINEL            = 25772,
    NPC_VOID_SPAWN               = 25824,
    NPC_SHADOWSWORD_BERSERKER    = 25798,
    NPC_SHADOWSWORD_FURY_MAGE    = 25799,
    NPC_SINGULARITY              = 25855,
    NPC_HAND_OF_DECEIVER         = 25588,
    NPC_KILJAEDEN                = 25315,
    NPC_SINISTER_REFLECTION      = 25708,
    NPC_SHIELD_ORB               = 25502,
    NPC_KALECGOS_DRAGON          = 24850,
    NPC_SATHROVARR               = 24892,
};

enum SunwellSpells : uint32
{
    SPELL_BURN                   = 46394,
    SPELL_BURN_DAMAGE            = 45141,
    SPELL_ENCAPSULATE            = 45661,
    SPELL_CONFLAGRATION          = 45342,
    SPELL_SHADOW_NOVA            = 45329,
    SPELL_FLAME_TOUCHED          = 45348,
    SPELL_DARK_TOUCHED           = 45347,
    SPELL_DARK_FLAME             = 45345,
    SPELL_FIRE_BLOOM             = 45641,
    SPELL_CURSE_BOUNDLESS_AGONY  = 45032,
    SPELL_SOUL_FLAY              = 45442,
};

bool InSunwell(Player* bot);
Unit* FindHostileByEntry(Player* bot, uint32 entry, float range = 150.0f);
bool BossCastingSpell(Unit* boss, uint32 spellId);
Unit* FindPriorityAdd(PlayerbotAI* botAI, Player* bot);
bool HasWrongTwinAuraForTarget(Player* bot, Unit* target);
}

#endif
