#ifndef BATTLE_H
#define BATTLE_H
#include <time.h>
#include <stdlib.h>
#include "../entities/character.h"
#include "../maps/location.h"

typedef struct {
    float criticalHit;
    float lifesteal;
} BuffBonus;

void damageApply(Player*, Rebel*, int);
void battleLog(Player*, Rebel*, int, BuffBonus, BuffBonus[], int);

#endif