/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license, you may redistribute it
 * and/or modify it under version 3 of the License, or (at your option), any later version.
 */

#include "PvpValues.h"

#include "BattlegroundEY.h"
#include "BattlegroundMgr.h"
#include "BattlegroundWS.h"
#include "Playerbots.h"
#include "ServerFacade.h"

Unit* FlagCarrierValue::Calculate()
{
    Unit* carrier = nullptr;

    if (botAI->GetBot()->InBattleground())
    {
        if (botAI->GetBot()->GetBattlegroundTypeId() == BattlegroundTypeId::BATTLEGROUND_WS)
        {
            BattlegroundWS* bg = (BattlegroundWS*)botAI->GetBot()->GetBattleground();

            if (!bg)
                return nullptr;

            if ((!sameTeam && bot->GetTeamId() == TEAM_HORDE || (sameTeam && bot->GetTeamId() == TEAM_ALLIANCE)) &&
                !bg->GetFlagPickerGUID(TEAM_HORDE).IsEmpty())
                carrier = ObjectAccessor::GetPlayer(bg->GetBgMap(), bg->GetFlagPickerGUID(TEAM_HORDE));

            if ((!sameTeam && bot->GetTeamId() == TEAM_ALLIANCE || (sameTeam && bot->GetTeamId() == TEAM_HORDE)) &&
                !bg->GetFlagPickerGUID(TEAM_ALLIANCE).IsEmpty())
                carrier = ObjectAccessor::GetPlayer(bg->GetBgMap(), bg->GetFlagPickerGUID(TEAM_ALLIANCE));

            if (carrier)
            {
                if (ignoreRange || bot->IsWithinDistInMap(carrier, sPlayerbotAIConfig.sightDistance))
                {
                    return carrier;
                }
                else
                    return nullptr;
            }
        }

        if (botAI->GetBot()->GetBattlegroundTypeId() == BATTLEGROUND_EY)
        {
            BattlegroundEY* bg = (BattlegroundEY*)botAI->GetBot()->GetBattleground();

            if (!bg)
                return nullptr;

            if (bg->GetFlagPickerGUID().IsEmpty())
                return nullptr;

            Player* fc = ObjectAccessor::GetPlayer(bg->GetBgMap(), bg->GetFlagPickerGUID());
            if (!fc)
                return nullptr;

            if (!sameTeam && (fc->GetTeamId() != bot->GetTeamId()))
                carrier = fc;

            if (sameTeam && (fc->GetTeamId() == bot->GetTeamId()))
                carrier = fc;

            if (carrier)
            {
                if (ignoreRange || bot->IsWithinDistInMap(carrier, sPlayerbotAIConfig.sightDistance))
                {
                    return carrier;
                }
                else
                    return nullptr;
            }
        }
    }

    return carrier;
}

std::vector<CreatureData const*> BgMastersValue::Calculate()
{
    BattlegroundTypeId bgTypeId = (BattlegroundTypeId)stoi(qualifier);

    std::vector<uint32> entries;
    std::map<TeamId, std::map<BattlegroundTypeId, std::vector<uint32>>> const& battleMastersCache =
        sRandomPlayerbotMgr.getBattleMastersCache();
    auto appendTeam = [&](TeamId teamId)
    {
        auto teamIt = battleMastersCache.find(teamId);
        if (teamIt == battleMastersCache.end())
            return;

        auto bgIt = teamIt->second.find(bgTypeId);
        if (bgIt == teamIt->second.end())
            return;

        entries.insert(entries.end(), bgIt->second.begin(), bgIt->second.end());
    };

    appendTeam(TEAM_NEUTRAL);
    appendTeam(TEAM_ALLIANCE);
    appendTeam(TEAM_HORDE);

    std::vector<CreatureData const*> bmGuids;

    for (auto entry : entries)
    {
        for (auto creaturePair : WorldPosition().getCreaturesNear(0, entry))
        {
            bmGuids.push_back(creaturePair);
        }
    }

    return bmGuids;
}

CreatureData const* BgMasterValue::Calculate()
{
    CreatureData const* bmPair = NearestBm(false);
    if (!bmPair)
        bmPair = NearestBm(true);

    return bmPair;
}

CreatureData const* BgMasterValue::NearestBm(bool allowDead)
{
    WorldPosition botPos(bot);

    std::vector<CreatureData const*> bmPairs = AI_VALUE2(std::vector<CreatureData const*>, "bg masters", qualifier);

    float rDist = 0.0f;
    CreatureData const* rbmPair = nullptr;

    for (auto& bmPair : bmPairs)
    {
        if (!bmPair)
            continue;

        WorldPosition bmPos(bmPair->mapid, bmPair->posX, bmPair->posY, bmPair->posZ, bmPair->orientation);

        float dist = botPos.distance(bmPos);  // This is the aproximate travel distance.

        // Did we already find a closer unit that is not dead?
        if (rbmPair && rDist <= dist)
            continue;

        CreatureTemplate const* bmTemplate = sObjectMgr->GetCreatureTemplate(bmPair->id1);
        if (!bmTemplate)
            continue;

        FactionTemplateEntry const* bmFactionEntry = sFactionTemplateStore.LookupEntry(bmTemplate->faction);

        // Is the unit hostile?
        if (Unit::GetFactionReactionTo(bot->GetFactionTemplateEntry(), bmFactionEntry) < REP_NEUTRAL)
            continue;

        AreaTableEntry const* area = bmPos.getArea();

        if (!area)
            continue;

        // Is the area hostile?
        if (area->team == 4 && bot->GetTeamId() == TEAM_ALLIANCE)
            continue;
        if (area->team == 2 && bot->GetTeamId() == TEAM_HORDE)
            continue;

        if (!allowDead)
        {
            Unit* unit = botAI->GetUnit(bmPair);

            if (!unit)
                continue;

            // Is the unit dead?
            if (unit->getDeathState() == DeathState::Dead)
                continue;
        }

        rbmPair = bmPair;
        rDist = dist;
    }

    return rbmPair;
}

BattlegroundTypeId RpgBgTypeValue::Calculate()
{
    GuidPosition guidPosition = AI_VALUE(GuidPosition, "rpg target");

    if (guidPosition)
        for (uint32 i = 1; i < MAX_BATTLEGROUND_QUEUE_TYPES; i++)
        {
            BattlegroundQueueTypeId queueTypeId = (BattlegroundQueueTypeId)i;

            BattlegroundTypeId bgTypeId = sBattlegroundMgr->BGTemplateId(queueTypeId);

            Battleground* bg = sBattlegroundMgr->GetBattlegroundTemplate(bgTypeId);
            if (!bg)
                continue;

            if (bot->GetLevel() < bg->GetMinLevel())
                continue;

            // check if already in queue
            if (bot->InBattlegroundQueueForBattlegroundQueueType(queueTypeId))
                continue;

            std::map<TeamId, std::map<BattlegroundTypeId, std::vector<uint32>>> const& battleMastersCache =
                sRandomPlayerbotMgr.getBattleMastersCache();

            auto matchesEntry = [&](TeamId teamId) -> bool
            {
                auto teamIt = battleMastersCache.find(teamId);
                if (teamIt == battleMastersCache.end())
                    return false;

                auto bgIt = teamIt->second.find(bgTypeId);
                if (bgIt == teamIt->second.end())
                    return false;

                for (uint32 entry : bgIt->second)
                    if (entry == guidPosition.GetEntry())
                        return true;

                return false;
            };

            if (matchesEntry(TEAM_NEUTRAL) || matchesEntry(bot->GetTeamId()))
                return bgTypeId;
        }

    return BATTLEGROUND_TYPE_NONE;
}
