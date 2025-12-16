#include <stdio.h>
#include <string.h>
#include "location.h"
#include "../entities/character.h"
#define lenCalc(arr) sizeof(arr)/sizeof(arr[0])

// Rebel_Stats rebel_melee = {100.0, 100.0, 25.0, 20.0, 0.25, 0.0};
// Rebel_Stats rebel_range = {85.0, 85.0, 35.0, 15.0, 0.40, 0.0};
// | NAME | MAX HP | HP | ATK | DEF | CRIT. CH. | LIFESTEAL CH. | STATE
Rebel eastGateEnemy[] = {
    {"Rebel 1", {100.0, 100.0, 25.0, 20.0, 0.25, 0.0}, ALIVE},
    {"Rebel 2", {85.0, 85.0, 35.0, 15.0, 0.40, 0.0}, ALIVE}
};
Rebel westGateEnemy[] = {
    {"Rebel 1", {100.0, 100.0, 25.0, 20.0, 0.25, 0.0}, ALIVE},
    {"Rebel 2", {100.0, 100.0, 25.0, 20.0, 0.25, 0.0}, ALIVE}
};

Location locations[] = {
    {"Benteng", 670.0, 670.0, NULL, 0},
    {"Gerbang Timur", 220.0, 220.0, eastGateEnemy, lenCalc(eastGateEnemy)},
    {"Gerbang Selatan", 220.0, 220.0, westGateEnemy, lenCalc(westGateEnemy)}
};

const int LOCATIONS_COUNT = sizeof(locations) / sizeof(locations[0]);

void changeLocation(Player *p, int idxLoc){
    strcpy(p->location, locations[idxLoc].name);
    p->inCombat = 1;
}

int locationIdx(Player p){
    for(int idx=0; idx<LOCATIONS_COUNT; idx++){
        if(strcmp(locations[idx].name, p.location) == 0)
            return idx;
    }
    return -1;
}