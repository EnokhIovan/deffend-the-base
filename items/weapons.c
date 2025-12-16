#include <stdio.h>
#include <string.h>
#include "weapons.h"

Weapons startUpWeapons[] = {    // | NAME | ATK | CRIT_CHANCE | LIFESTEAL_CHANCE
    {"Altreas", 20, 0.45, 0.20},
    {"Ferwash", 30, 0.15, 0.45}
};

const int STARTUP_WEAPONS_COUNT = sizeof(startUpWeapons) / sizeof(startUpWeapons[0]);

void weaponsAffect(Player *p, Weapons w){
    strcpy(p->weapon, w.name);
    p->atk += w.atk;
    p->critC += w.critC;
    p->lsC += w.lsC;
}