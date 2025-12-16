#ifndef BATTLE_H
#define BATTLE_H
#include <time.h>
#include <stdlib.h>
#include "../entities/character.h"
#include "../maps/location.h"

void damageApply(Player*, Rebel*, int);
void battleLog();

#endif