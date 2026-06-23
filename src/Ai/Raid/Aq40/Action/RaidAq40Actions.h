#ifndef _PLAYERBOT_RAIDAQ40ACTIONS_H
#define _PLAYERBOT_RAIDAQ40ACTIONS_H

#include "AttackAction.h"
#include "MovementActions.h"

class Aq40MoveFromBossAction : public MovementAction
{
public:
    Aq40MoveFromBossAction(PlayerbotAI* botAI, std::string const name, float distance)
        : MovementAction(botAI, name), _distance(distance) {}
    bool Execute(Event event) override;

protected:
    virtual Unit* GetBoss() = 0;

private:
    float _distance;
};

class Aq40SkeramMoveAwayAction : public Aq40MoveFromBossAction
{
public:
    Aq40SkeramMoveAwayAction(PlayerbotAI* botAI)
        : Aq40MoveFromBossAction(botAI, "aq40 skeram move away", 25.0f) {}
protected:
    Unit* GetBoss() override;
};

class Aq40MoveFromGroupSpreadAction : public MovementAction
{
public:
    Aq40MoveFromGroupSpreadAction(PlayerbotAI* botAI, std::string const name,
        float distance = 22.0f)
        : MovementAction(botAI, name), _distance(distance) {}
    bool Execute(Event event) override;

private:
    float _distance;
};

class Aq40SarturaMoveAwayAction : public MovementAction
{
public:
    Aq40SarturaMoveAwayAction(PlayerbotAI* botAI)
        : MovementAction(botAI, "aq40 sartura move away") {}
    bool Execute(Event event) override;
};

class Aq40TwinsMoveFromVeklorAction : public MovementAction
{
public:
    Aq40TwinsMoveFromVeklorAction(PlayerbotAI* botAI)
        : MovementAction(botAI, "aq40 twins move from veklor") {}
    bool Execute(Event event) override;
};

class Aq40TwinsSwitchTargetAction : public AttackAction
{
public:
    Aq40TwinsSwitchTargetAction(PlayerbotAI* botAI)
        : AttackAction(botAI, "aq40 twins switch target") {}
    bool Execute(Event event) override;
};

class Aq40TwinsVeklorTankRangeAction : public AttackAction
{
public:
    Aq40TwinsVeklorTankRangeAction(PlayerbotAI* botAI)
        : AttackAction(botAI, "aq40 twins veklor tank range") {}
    bool Execute(Event event) override;
};

class Aq40CthunMoveFromBeamAction : public Aq40MoveFromBossAction
{
public:
    Aq40CthunMoveFromBeamAction(PlayerbotAI* botAI)
        : Aq40MoveFromBossAction(botAI, "aq40 cthun move from dark glare", 45.0f) {}
protected:
    Unit* GetBoss() override;
};

class Aq40CthunMoveFromGreenBeamAction : public Aq40MoveFromBossAction
{
public:
    Aq40CthunMoveFromGreenBeamAction(PlayerbotAI* botAI)
        : Aq40MoveFromBossAction(botAI, "aq40 cthun move from green beam", 35.0f) {}
protected:
    Unit* GetBoss() override;
};

class Aq40MoveFromSlimeAction : public MovementAction
{
public:
    Aq40MoveFromSlimeAction(PlayerbotAI* botAI)
        : MovementAction(botAI, "aq40 move from slime") {}
    bool Execute(Event event) override;
};

class Aq40AttackPriorityAddAction : public AttackAction
{
public:
    Aq40AttackPriorityAddAction(PlayerbotAI* botAI)
        : AttackAction(botAI, "aq40 attack priority add") {}
    bool Execute(Event event) override;
};

#endif
