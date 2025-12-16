#ifndef ARMOURS_H
#define ARMOURS_H
#include "../entities/character.h"

typedef struct {
    char name[16];
    int hp;
    int def;
} Armours;

extern const int STARTUP_ARMOURS_COUNT;
extern Armours startUpArmours[];

void armoursAffect(Player *p, Armours a);

#endif