#ifndef _PLAYERBOT_RAIDAQ40HELPERS_H
#define _PLAYERBOT_RAIDAQ40HELPERS_H

#include "PlayerbotAI.h"
#include "Playerbots.h"

#include <cstdint>
#include <vector>

namespace Aq40Helpers
{
constexpr uint32 AQ40_MAP_ID = 531;

enum Aq40Npcs : uint32
{
    NPC_PROPHET_SKERAM          = 15263,
    NPC_LORD_KRI                = 15511,
    NPC_VEM                     = 15544,
    NPC_PRINCESS_YAUJ           = 15543,
    NPC_YAUJ_BROOD              = 15621,
    NPC_BATTLEGUARD_SARTURA     = 15516,
    NPC_SARTURA_GUARD           = 15984,
    NPC_FANKRISS                = 15510,
    NPC_VEKNISS_HATCHLING       = 15962,
    NPC_VISCIDUS                = 15299,
    NPC_GLOB_OF_VISCIDUS        = 15667,
    NPC_TOXIC_SLIME             = 15925,
    NPC_PRINCESS_HUHURAN        = 15509,
    NPC_EMPEROR_VEKNILASH       = 15275,
    NPC_EMPEROR_VEKLOR          = 15276,
    NPC_QIRAJI_SCARAB           = 15316,
    NPC_QIRAJI_SCORPION         = 15317,
    NPC_OURO                    = 15517,
    NPC_OURO_SCARAB             = 15718,
    NPC_EYE_OF_CTHUN            = 15589,
    NPC_CTHUN                   = 15727,
    NPC_CLAW_TENTACLE           = 15725,
    NPC_EYE_TENTACLE            = 15726,
    NPC_GIANT_CLAW_TENTACLE     = 15728,
    NPC_GIANT_EYE_TENTACLE      = 15334,
    NPC_FLESH_TENTACLE          = 15802,
};

enum Aq40Spells : uint32
{
    SPELL_ARCANE_EXPLOSION      = 26192,
    SPELL_TRUE_FULFILLMENT      = 785,
    SPELL_TOXIC_VOLLEY          = 25812,
    SPELL_WHIRLWIND             = 26083,
    SPELL_GUARD_WHIRLWIND       = 26038,
    SPELL_POISONBOLT_VOLLEY     = 25991,
    SPELL_NOXIOUS_POISON        = 26053,
    SPELL_WYVERN_STING          = 26180,
    SPELL_BLIZZARD              = 26607,
    SPELL_ARCANE_BURST          = 568,
    SPELL_GROUND_RUPTURE        = 26100,
    SPELL_DARK_GLARE            = 26029,
    SPELL_GREEN_BEAM            = 26134,
};

bool InAq40(Player* bot);
Unit* FindHostileByEntry(Player* bot, uint32 entry, float range = 150.0f);
Unit* FindCThunEyeOrBody(Player* bot);
bool BossCastingSpell(Unit* boss, uint32 spellId);
Unit* FindPriorityAdd(PlayerbotAI* botAI, Player* bot);
bool AnyBugTrioActive(PlayerbotAI* botAI, Player* bot);
bool TwinsFightActive(PlayerbotAI* botAI, Player* bot);
bool CthunFightActive(Player* bot);
uint32 GetAssignedTwinEmperorEntry(PlayerbotAI* botAI, Player* bot);
Unit* GetAssignedTwinEmperor(PlayerbotAI* botAI, Player* bot);
}

#endif
