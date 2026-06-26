/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license, you may redistribute it
 * and/or modify it under version 3 of the License, or (at your option), any later version.
 */

#ifndef _PLAYERBOT_RANDOMPLAYERBOTFACTORY_H
#define _PLAYERBOT_RANDOMPLAYERBOTFACTORY_H

#include <map>
#include <unordered_map>
#include <vector>

#include "Common.h"
#include "DBCEnums.h"

class Player;
class ArenaTeam;
class WorldSession;

enum ArenaType : uint8;

class RandomPlayerbotFactory
{
public:
    enum class NameRaceAndGender : uint8
    {
        // Generic is the category used for human & undead
        GenericMale = 0,
        GenericFemale,
        GnomeMale,
        GnomeFemale,
        DwarfMale,
        DwarfFemale,
        NightelfMale,
        NightelfFemale,
        DraeneiMale,
        DraeneiFemale,
        OrcMale,
        OrcFemale,
        TrollMale,
        TrollFemale,
        TaurenMale,
        TaurenFemale,
        BloodelfMale,
        BloodelfFemale
    };

    static constexpr NameRaceAndGender CombineRaceAndGender(uint8 race, uint8 gender);

    RandomPlayerbotFactory() {};
    virtual ~RandomPlayerbotFactory() {}

    Player* CreateRandomBot(WorldSession* session, uint8 cls, std::unordered_map<NameRaceAndGender, std::vector<std::string>>& names);
    static void CreateRandomBots();
    static void CreateRandomArenaTeams(ArenaType slot, uint32 count, uint8 forcedLevel = 0);
    static void EnsureRandomArenaTeams();
    static bool CanCreateRandomBotArenaTeams();
    static bool HasRequiredRandomBotArenaTeams();
    static bool IsRandomBotArenaTeamCreationExhausted(ArenaType type, uint8 forcedLevel);
    static void MarkRandomBotArenaTeamCreationExhausted(ArenaType type, uint8 forcedLevel, uint32 created,
                                                        uint32 target);
    static void ClearRandomBotArenaTeamCreationExhausted();
    static void RemoveRandomBotArenaTeam(ArenaTeam* team);
    static uint32 GetRandomBotArenaTeamTargetCount(ArenaType type, uint8 forcedLevel);
    static uint32 CountRandomBotArenaTeams(ArenaType type, uint8 forcedLevel);
    static void PrepareBotArenaLevel(Player* player, uint8 targetLevel);
    static void RepinRandomBotArenaCaptains();
    static uint8 GetRandomBotArenaTeamBracketLevel(ArenaTeam* team);
    static uint8 GetRandomBotArenaBracketLevel(Player* bot);
    static bool IsRandomBotArenaLevel70FeaturesEnabled();
    static bool ShouldLockRandomBotArenaLevel(uint8 bracket);
    static bool ShouldPinRandomBotArenaFillers(uint8 bracket);
    static void ApplyRandomBotArenaLevelPolicy(Player* bot, uint8 bracket);
    static void RefreshRandomBotArenaLevelPolicy(Player* bot);
    static void RepinRandomBotArenaTeamForQueue(ArenaTeam* team);
    static std::string const CreateRandomGuildName();
    static uint32 CalculateTotalAccountCount();
    static uint32 CalculateAvailableCharsPerAccount();

private:
    static uint32 ArenaTeamCreationKey(ArenaType type, uint8 forcedLevel);
    static bool IsRandomBotArenaBracketSatisfied(ArenaType type, uint8 forcedLevel, uint32 targetCount);
    static bool IsValidRaceClassCombination(uint8 race, uint8 class_, uint32 expansion);
    std::string const CreateRandomBotName(NameRaceAndGender raceAndGender);
    static std::string const CreateRandomArenaTeamName();
};

#endif
