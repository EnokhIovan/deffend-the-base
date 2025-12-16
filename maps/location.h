#ifndef LOCATION_H
#define LOCATION_H
#include "../entities/character.h"
#define ENEMY_MAX 2

typedef struct {
    char name[32];
    float maxHP;
    float hp;
    Rebel *enemy;
    int enemyCount;
} Location;

void changeLocation(Player*, int);
int locationIdx(Player);

extern const int LOCATIONS_COUNT;
extern Location locations[];

#endif