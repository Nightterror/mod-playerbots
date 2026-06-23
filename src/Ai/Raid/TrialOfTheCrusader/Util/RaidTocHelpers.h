#ifndef _PLAYERBOT_RAIDTOCHELPERS_H
#define _PLAYERBOT_RAIDTOCHELPERS_H

#include "PlayerbotAI.h"
#include "Playerbots.h"

#include <cstdint>

namespace TocHelpers
{
constexpr uint32 TOC_MAP_ID = 649;

enum TocNpcs : uint32
{
    NPC_GORMOK                   = 34796,
    NPC_SNOBOLD                  = 34800,
    NPC_FIRE_BOMB                = 34854,
    NPC_DREADSCALE               = 34799,
    NPC_ACIDMAW                  = 35144,
    NPC_ICEHOWL                  = 34797,
    NPC_JARAXXUS                 = 34780,
    NPC_LEGION_FLAME             = 34784,
    NPC_FELFLAME_INFERNAL        = 34815,
    NPC_MISTRESS_OF_PAIN         = 34826,
    NPC_FJOLA                    = 34497,
    NPC_EYDIS                    = 34496,
    NPC_LIGHT_BALL               = 34630,
    NPC_DARK_BALL                = 34628,
    NPC_ANUBARAK                 = 34564,
    NPC_ANUB_SPIKE               = 34660,
    NPC_NERUBIAN_BURROWER        = 34607,
    NPC_SWARM_SCARAB             = 34605,
    NPC_FROST_SPHERE             = 34606,
};

enum TocSpells : uint32
{
    SPELL_LEGION_FLAME           = 66197,
    SPELL_INCINERATE_FLESH       = 66237,
    SPELL_MASSIVE_CRASH          = 66683,
    SPELL_PENETRATING_COLD       = 66013,
    SPELL_MARK_OF_SPIKE          = 67574,
    SPELL_LIGHT_ESSENCE          = 65686,
    SPELL_DARK_ESSENCE           = 65684,
    SPELL_LIGHT_VORTEX           = 66046,
    SPELL_DARK_VORTEX            = 66058,
    SPELL_LIGHT_SHIELD           = 65858,
    SPELL_DARK_SHIELD            = 65874,
};

static uint32 const HEALER_ENTRIES[] =
{
    34469, 34459, 34465, 34445, 34466, 34447, 34470, 34444
};

static uint32 const CASTER_ENTRIES[] =
{
    34468, 34449, 34473, 34441, 34467, 34448, 34474, 34450
};

bool InToc(Player* bot);
Unit* FindHostileByEntry(Player* bot, uint32 entry, float range = 150.0f);
bool BossCastingSpell(Unit* boss, uint32 spellId);
Unit* FindPriorityAdd(PlayerbotAI* botAI, Player* bot);
Unit* FindTocChampionTarget(PlayerbotAI* botAI, Player* bot);
bool IsTocHealerEntry(uint32 entry);
bool IsTocCasterEntry(uint32 entry);
bool HasLightEssence(Player* bot);
bool HasDarkEssence(Player* bot);
}

#endif
