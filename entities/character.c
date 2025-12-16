#include <stdio.h>
#include <string.h>
#include "character.h"
#include "../maps/location.h"

void initPlayer(Player *p, const char *name) {
    strcpy(p->name, name);
    p->maxHP = 100.0;
    p->hp = 100.0;
    p->atk = 15.0;
    p->def = 10.0;
    strcpy(p->weapon, "None");
    strcpy(p->armour, "None");
    p->critC = 0.0;
    p->lsC = 0.0;
    strcpy(p->location, "Rumah");
    p->inCombat = 0;
    p->state = ALIVE;
}

void printPlayer(Player *p){
    printf("%s | HP: %.1f / %.1f | ATK: %.1f | DEF: %.1f | Senjata: %s | Armor: %s | Crit. Ch.: %.0f%% | LS Ch.: %.0f%%\nLokasi: %s\n",
        p->name, p->hp, p->maxHP, p->atk, p->def, p->weapon, p->armour, p->critC*100, p->lsC*100, p->location);
}