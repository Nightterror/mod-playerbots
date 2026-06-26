/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license, you may redistribute it
 * and/or modify it under version 3 of the License, or (at your option), any later version.
 */

#include "PartyMemberWithoutAuraValue.h"
#include "PartyMemberNeedingGroupBuffValue.h"
#include "PartyMemberNeedingPaladinBlessingValue.h"

#include "GenericBuffUtils.h"
#include "Playerbots.h"

extern std::vector<std::string> split(std::string const s, char delim);

class PlayerWithoutAuraPredicate : public FindPlayerPredicate, public PlayerbotAIAware
{
public:
    PlayerWithoutAuraPredicate(PlayerbotAI* botAI, std::string const aura)
        : PlayerbotAIAware(botAI), FindPlayerPredicate(), auras(split(aura, ','))
    {
    }

public:
    bool Check(Unit* unit) override
    {
        if (!unit->IsAlive())
            return false;

        for (std::vector<std::string>::iterator i = auras.begin(); i != auras.end(); ++i)
        {
            if (botAI->HasAura(*i, unit))
                return false;
        }

        return true;
    }

private:
    std::vector<std::string> auras;
};

Unit* PartyMemberWithoutAuraValue::Calculate()
{
    PlayerWithoutAuraPredicate predicate(botAI, qualifier);
    return FindPartyMember(predicate);
}

class PartyMemberNeedingPaladinBlessingPredicate : public FindPlayerPredicate, public PlayerbotAIAware
{
public:
    PartyMemberNeedingPaladinBlessingPredicate(PlayerbotAI* botAI, std::string const blessingBase)
        : PlayerbotAIAware(botAI), FindPlayerPredicate(), blessingBase(blessingBase)
    {
    }

    bool Check(Unit* unit) override
    {
        return ai::buff::NeedsPaladinBlessing(botAI, unit, blessingBase);
    }

private:
    std::string blessingBase;
};

Unit* PartyMemberNeedingPaladinBlessingValue::Calculate()
{
    PartyMemberNeedingPaladinBlessingPredicate predicate(botAI, qualifier);
    return FindPartyMember(predicate);
}

class PartyMemberNeedingGroupBuffPredicate : public FindPlayerPredicate, public PlayerbotAIAware
{
public:
    PartyMemberNeedingGroupBuffPredicate(PlayerbotAI* botAI, std::string const singleBase)
        : PlayerbotAIAware(botAI), FindPlayerPredicate(), singleBase(singleBase)
    {
    }

    bool Check(Unit* unit) override
    {
        return ai::buff::NeedsGroupBuff(botAI, unit, singleBase);
    }

private:
    std::string singleBase;
};

Unit* PartyMemberNeedingGroupBuffValue::Calculate()
{
    PartyMemberNeedingGroupBuffPredicate predicate(botAI, qualifier);
    return FindPartyMember(predicate);
}
