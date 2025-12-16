#include <stdio.h>
#include "battle.h"

float defCalc(float dmg, float def){
    return (dmg > def) ? def : def-1;
}

void battleLog(Player *p, Rebel *r, int attackIdx, BuffBonus pB, BuffBonus rB[]){
    printf("\nKamu menyerang %s dan memberikan kerusakan sebanyak (%.1f+%.1f) - (%.1f) HP dan mendapat lifesteal sebanyak (%.1f) HP",
        r[attackIdx].name,
        p->atk,
        pB.criticalHit,
        defCalc(p->atk + pB.criticalHit, r[attackIdx].stats.def),
        pB.lifesteal
    );
    for(int idx=0; idx<locations[locationIdx(*p)].enemyCount; idx++){
        printf("\n%s menyerangmu dan memberikan kerusakan sebanyak (%.1f+%.1f) - (%.1f) HP dan mendapat lifesteal sebanyak (%.1f) HP",
            r[idx].name,
            r[idx].stats.atk,
            rB[idx].criticalHit,
            defCalc(r[idx].stats.atk + rB[idx].criticalHit, p->def),
            rB[idx].lifesteal
        );
    }
    printf("\n");
}

void damageApply(Player *p, Rebel *r, int attackIdx){
    BuffBonus playerBonus;
    BuffBonus rebelBonus[2];

    float playerDamage = (((float)rand() / (float)RAND_MAX) < p->critC) ? p->atk*2 : p->atk;
    float playerLifesteal = (((float)rand() / (float)RAND_MAX) < p->lsC) ? playerDamage/2 : 0;
    float playerFinalLifesteal = (p->hp + playerLifesteal >= p->maxHP) ? p->maxHP-p->hp : playerLifesteal;
    playerBonus.criticalHit = playerDamage - p->atk;
    playerBonus.lifesteal = playerFinalLifesteal;
    
    r[attackIdx].stats.hp -= (playerDamage - r[attackIdx].stats.def <= 0) ? 1 : playerDamage - r[attackIdx].stats.def;
    p->hp += playerFinalLifesteal;
    
    for(int idx=0; idx<locations[locationIdx(*p)].enemyCount; idx++){
        float rebelDamage = (((float)rand() / (float)RAND_MAX) < r[idx].stats.critC) ? r[idx].stats.atk*2 : r[idx].stats.atk;
        float rebelLifesteal = (((float)rand() / (float)RAND_MAX) < r[idx].stats.lsC) ? rebelDamage/2 : 0;
        float rebelFinalLifesteal = (r[idx].stats.hp + rebelLifesteal >= r[idx].stats.maxHP) ? r[idx].stats.maxHP-r[idx].stats.hp : rebelLifesteal;

        rebelBonus[idx].criticalHit = rebelDamage-r[idx].stats.atk;
        rebelBonus[idx].lifesteal = rebelFinalLifesteal;

        p->hp -= (rebelDamage - p->def <= 0) ? 1 : rebelDamage - p->def;
        r[idx].stats.hp += rebelFinalLifesteal;
    }

    battleLog(p, r, attackIdx, playerBonus, rebelBonus);
}