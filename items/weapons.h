#ifndef WEAPONS_H
#define WEAPONS_H
#include "../entities/character.h"

typedef struct {
    char name[16];
    int atk;
    float critC;
    float lsC;
} Weapons;

extern const int STARTUP_WEAPONS_COUNT;
extern Weapons startUpWeapons[];

void weaponsAffect(Player *p, Weapons w);

#endif