/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license, you may redistribute it
 * and/or modify it under version 3 of the License, or (at your option), any later version.
 */

#pragma once

#include <string>
#include <functional>
#include "Common.h"
#include "Group.h"
#include "Chat.h"
#include "Language.h"

class Player;
class PlayerbotAI;

namespace ai::buff
{

// All paladin blessings share one exclusive slot (spell group 1010).
inline char const* AllPaladinBlessingAuras =
    "blessing of might,greater blessing of might,"
    "blessing of wisdom,greater blessing of wisdom,"
    "blessing of kings,greater blessing of kings,"
    "blessing of sanctuary,greater blessing of sanctuary";

// Build an aura qualifier "single + greater" to avoid double-buffing
std::string MakeAuraQualifierForBuff(std::string const& name);

// Maps a group/raid buff name to its single-target counterpart.
std::string SingleVariantFor(std::string const& groupName);

// True when a unit should receive a group buff cast (Prayer of Fortitude, Gift of
// the Wild, etc.). Individual buffs block fortitude group casts; other lines allow
// upgrading single -> group.
bool NeedsGroupBuff(PlayerbotAI* botAI, Unit* unit, std::string const& singleBase);

// True when unit lacks the desired paladin blessing and is not blocked by a
// different blessing type (greater variant of the desired blessing counts as
// satisfied).
bool NeedsPaladinBlessing(PlayerbotAI* botAI, Unit* unit, std::string const& blessingBase);

// Returns the group spell name for a given single-target buff.
// If no group equivalent exists, returns "".
std::string GroupVariantFor(std::string const& name);

// Checks if the bot has the required reagents to cast a spell (by its spellId).
// Returns false if the spellId is invalid.
bool HasRequiredReagents(Player* bot, uint32 spellId);

// Applies the "switch to group buff" policy if: the bot is in a group of size x+,
// the group variant is known/useful, and reagents are available. Otherwise, returns baseName.
// If announceOnMissing == true and reagents are missing, calls the 'announce' callback
// (if provided) to notify the party/raid.
std::string UpgradeToGroupIfAppropriate(
    Player* bot,
    PlayerbotAI* botAI,
    std::string const& baseName,
    bool announceOnMissing = false,
    std::function<void(std::string const&)> announce = {}
    );
}

namespace ai::spell
{
    bool HasSpellOrCategoryCooldown(Player* bot, uint32 spellId);
}

namespace ai::chat {
    inline std::function<void(std::string const&)> MakeGroupAnnouncer(Player* me)
    {
        return [me](std::string const& msg)
        {
            if (Group* g = me->GetGroup())
            {
                WorldPacket data;
                ChatMsg type = g->isRaidGroup() ? CHAT_MSG_RAID : CHAT_MSG_PARTY;
                ChatHandler::BuildChatPacket(data, type, LANG_UNIVERSAL, me, /*receiver=*/nullptr, msg.c_str());
                g->BroadcastPacket(&data, true, -1, me->GetGUID());
            }
            else
            {
                me->Say(msg, LANG_UNIVERSAL);
            }
        };
    }
}
