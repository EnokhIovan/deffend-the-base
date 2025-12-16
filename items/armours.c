#include <stdio.h>
#include <string.h>
#include "armours.h"

Armours startUpArmours[] = {    // | NAME | HP | DEF |
    {"Aegis", 100, 35},
    {"Titanis", 165, 15}
};

const int STARTUP_ARMOURS_COUNT = sizeof(startUpArmours) / sizeof(startUpArmours[0]);

void armoursAffect(Player *p, Armours a){
    strcpy(p->armour, a.name);
    p->maxHP += a.hp;
    p->hp += a.hp;
    p->def += a.def;
}