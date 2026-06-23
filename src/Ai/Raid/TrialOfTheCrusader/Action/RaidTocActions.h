#ifndef _PLAYERBOT_RAIDTOCACTIONS_H
#define _PLAYERBOT_RAIDTOCACTIONS_H

#include "AttackAction.h"
#include "MovementActions.h"

class TocMoveFromGroupAction : public MovementAction
{
public:
    TocMoveFromGroupAction(PlayerbotAI* botAI, std::string const name, float distance = 24.0f)
        : MovementAction(botAI, name), _distance(distance) {}
    bool Execute(Event event) override;

private:
    float _distance;
};

class TocMoveFromIcehowlAction : public MovementAction
{
public:
    TocMoveFromIcehowlAction(PlayerbotAI* botAI)
        : MovementAction(botAI, "toc move from icehowl") {}
    bool Execute(Event event) override;
};

class TocMoveFromFireBombAction : public MovementAction
{
public:
    TocMoveFromFireBombAction(PlayerbotAI* botAI)
        : MovementAction(botAI, "toc move from fire bomb") {}
    bool Execute(Event event) override;
};

class TocAttackPriorityAddAction : public AttackAction
{
public:
    TocAttackPriorityAddAction(PlayerbotAI* botAI)
        : AttackAction(botAI, "toc attack priority add") {}
    bool Execute(Event event) override;
};

class TocAttackFactionChampionAction : public AttackAction
{
public:
    TocAttackFactionChampionAction(PlayerbotAI* botAI)
        : AttackAction(botAI, "toc attack faction champion") {}
    bool Execute(Event event) override;
};

class TocTwinSwitchTargetAction : public AttackAction
{
public:
    TocTwinSwitchTargetAction(PlayerbotAI* botAI)
        : AttackAction(botAI, "toc twin switch target") {}
    bool Execute(Event event) override;
};

class TocTwinStopDpsAction : public MovementAction
{
public:
    TocTwinStopDpsAction(PlayerbotAI* botAI)
        : MovementAction(botAI, "toc twin stop dps") {}
    bool Execute(Event event) override;
};

#endif
