#include <stdio.h>
#include <string.h>
#include "battle.h"

float defCalc(float dmg, float def){
    return (dmg > def) ? def : dmg-1;
}

void battleLog(Player *p, Rebel *r, int attackIdx, BuffBonus pB, BuffBonus rB[], int idxMurder){
    char stateSen[2][32];
    sprintf(stateSen[0], (r[attackIdx].state == DEAD) ? 
        "membunuh %s dengan" : "menyerang %s dan",
        r[attackIdx].name
    );

    printf("\nKamu %s memberikan kerusakan sebanyak (%.1f+%.1f) - (%.1f) HP dan mendapat lifesteal sebanyak (%.1f) HP",
        stateSen[0],
        p->atk,
        pB.criticalHit,
        defCalc(p->atk + pB.criticalHit, r[attackIdx].stats.def),
        pB.lifesteal
    );
    for(int idx=0; idx<locations[locationIdx(*p)].enemyCount; idx++){
        if (r[idx].state == ALIVE){
            sprintf(stateSen[1], (p->state == DEAD && idx == idxMurder) ?
                "%s membunuhmu dengan" : "%s menyerangmu dan",
                r[idx].name
            );
    
            printf("\n%s memberikan kerusakan sebanyak (%.1f+%.1f) - (%.1f) HP dan mendapat lifesteal sebanyak (%.1f) HP",
                stateSen[1],
                r[idx].stats.atk,
                rB[idx].criticalHit,
                defCalc(r[idx].stats.atk + rB[idx].criticalHit, p->def),
                rB[idx].lifesteal
            );
        }
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

    if(r[attackIdx].stats.hp <= 0)
        r[attackIdx].state = DEAD;
    
    for(int idx=0; idx<locations[locationIdx(*p)].enemyCount; idx++){
        if (p->state == ALIVE && r[idx].state == ALIVE){
            float rebelDamage = (((float)rand() / (float)RAND_MAX) < r[idx].stats.critC) ? r[idx].stats.atk*2 : r[idx].stats.atk;
            float rebelLifesteal = (((float)rand() / (float)RAND_MAX) < r[idx].stats.lsC) ? rebelDamage/2 : 0;
            float rebelFinalLifesteal = (r[idx].stats.hp + rebelLifesteal >= r[idx].stats.maxHP) ? r[idx].stats.maxHP-r[idx].stats.hp : rebelLifesteal;
    
            rebelBonus[idx].criticalHit = rebelDamage-r[idx].stats.atk;
            rebelBonus[idx].lifesteal = rebelFinalLifesteal;
    
            p->hp -= (rebelDamage - p->def <= 0) ? 1 : rebelDamage - p->def;
            r[idx].stats.hp += rebelFinalLifesteal;
    
            if(p->hp <= 0){
                p->state = DEAD;
                battleLog(p, r, attackIdx, playerBonus, rebelBonus, idx);
                return ;
            }
        }
    }

    battleLog(p, r, attackIdx, playerBonus, rebelBonus, -1);
}