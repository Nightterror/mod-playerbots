#ifndef _PLAYERBOT_RAIDRUBYSANCTUMACTIONS_H
#define _PLAYERBOT_RAIDRUBYSANCTUMACTIONS_H

#include "AttackAction.h"
#include "MovementActions.h"

class RsMoveFromBaltharusAction : public MovementAction
{
public:
    RsMoveFromBaltharusAction(PlayerbotAI* botAI, std::string const name = "ruby sanctum move from baltharus")
        : MovementAction(botAI, name) {}
    bool Execute(Event event) override;
};

class RsMoveFromGroupConflagrationAction : public MovementAction
{
public:
    RsMoveFromGroupConflagrationAction(PlayerbotAI* botAI,
        std::string const name = "ruby sanctum move from group conflagration")
        : MovementAction(botAI, name) {}
    bool Execute(Event event) override;
};

class RsMoveFromGroupHalionMarkAction : public MovementAction
{
public:
    RsMoveFromGroupHalionMarkAction(PlayerbotAI* botAI,
        std::string const name = "ruby sanctum move from group halion mark")
        : MovementAction(botAI, name) {}
    bool Execute(Event event) override;
};

class RsAvoidMeteorFlameAction : public MovementAction
{
public:
    RsAvoidMeteorFlameAction(PlayerbotAI* botAI, std::string const name = "ruby sanctum avoid meteor flame")
        : MovementAction(botAI, name) {}
    bool Execute(Event event) override;
};

class RsAttackFlamecallerAction : public AttackAction
{
public:
    RsAttackFlamecallerAction(PlayerbotAI* botAI, std::string const name = "ruby sanctum attack flamecaller")
        : AttackAction(botAI, name) {}
    bool Execute(Event event) override;
};

#endif
