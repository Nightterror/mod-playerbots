#ifndef _PLAYERBOT_RAIDSUNWELLACTIONS_H
#define _PLAYERBOT_RAIDSUNWELLACTIONS_H

#include "AttackAction.h"
#include "MovementActions.h"

class SwMoveFromGroupAction : public MovementAction
{
public:
    SwMoveFromGroupAction(PlayerbotAI* botAI, std::string const name, float distance = 24.0f)
        : MovementAction(botAI, name), _distance(distance) {}
    bool Execute(Event event) override;

private:
    float _distance;
};

class SwMoveFromUnitAction : public MovementAction
{
public:
    SwMoveFromUnitAction(PlayerbotAI* botAI, std::string const name, uint32 entry,
        float searchRange, float moveDistance)
        : MovementAction(botAI, name), _entry(entry), _searchRange(searchRange),
          _moveDistance(moveDistance) {}
    bool Execute(Event event) override;

private:
    uint32 _entry;
    float _searchRange;
    float _moveDistance;
};

class SwAttackPriorityAddAction : public AttackAction
{
public:
    SwAttackPriorityAddAction(PlayerbotAI* botAI)
        : AttackAction(botAI, "sunwell attack priority add") {}
    bool Execute(Event event) override;
};

class SwTwinsSwitchTargetAction : public AttackAction
{
public:
    SwTwinsSwitchTargetAction(PlayerbotAI* botAI)
        : AttackAction(botAI, "sunwell twins switch target") {}
    bool Execute(Event event) override;
};

class SwKalecgosRealmTargetAction : public AttackAction
{
public:
    SwKalecgosRealmTargetAction(PlayerbotAI* botAI)
        : AttackAction(botAI, "sunwell kalecgos realm target") {}
    bool Execute(Event event) override;
    bool isUseful() override;
};

#endif
