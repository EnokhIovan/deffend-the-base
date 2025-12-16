#ifndef CHARACTER_H
#define CHARACTER_H
#include <stdbool.h>

typedef struct {
    char name[32];
    float maxHP;
    float hp;
    float atk;
    float def;
    char weapon[32];
    char armour[32];
    float critC;
    float lsC;
    char location[32];
    bool inCombat;
} Player;

typedef struct {
    float maxHP;
    float hp;
    float atk;
    float def;
    float critC;
    float lsC;
} Rebel_Stats;

typedef struct {
    char name[16];
    Rebel_Stats stats;
} Rebel;

void initPlayer(Player *p, const char *name);
void printPlayer(Player *p);

#endif