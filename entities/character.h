#ifndef CHARACTER_H
#define CHARACTER_H
#include <stdbool.h>

typedef enum {
    ALIVE,
    DEAD,
    STUNNED
} EntityState;

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
    EntityState state;
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
    EntityState state;
} Rebel;

void initPlayer(Player *p, const char *name);
void printPlayer(Player *p);

#endif