#include <stdio.h>
#include "battle.h"

void damageApply(Player *p, Rebel *r, int attackIdx){
    float playerDamage = (((float)rand() / (float)RAND_MAX) < p->critC) ? p->atk*2 : p->atk;
    r[attackIdx].stats.hp -= (playerDamage - r[attackIdx].stats.def <= 0) ? 1 : playerDamage - r[attackIdx].stats.def;

    for(int idx=0; idx<locations[locationIdx(*p)].enemyCount; idx++){
        float rebelDamage = (((float)rand() / (float)RAND_MAX) < r[idx].stats.critC) ? r[idx].stats.atk*2 : r[idx].stats.atk;
        p->hp -= (rebelDamage - p->def <= 0) ? 1 : rebelDamage - p->def;
    }
}

// void battleLog(){

// }