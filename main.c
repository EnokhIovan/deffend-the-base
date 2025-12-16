#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "entities/character.h"
#include "items/armours.h"
#include "items/weapons.h"
#include "maps/location.h"
#include "core/battle.h"

void stateSprt(int);
void chooseWeapon(Player*, Weapons[], int);
void chooseArmours(Player*, Armours[], int);
int stateCount=0;

int main(){
    Player player;
    srand(time(NULL));
    char playerName[32];

    //Pengisian Nama
    printf("\nHalo, Selamat datang di Deffend the Base!");
    printf("\nSilahkan masukkan karakter anda!\nNama: ");
    scanf(" %[^\n]s", playerName);
    initPlayer(&player, playerName);
    
    //Pengambilan Senjata & Armor
    chooseWeapon(&player, startUpWeapons, STARTUP_WEAPONS_COUNT);
    chooseArmours(&player, startUpArmours, STARTUP_ARMOURS_COUNT);

    
    bool gameStats = 0;
    int userAtkChoice;
    printf("\nBagus! Kamu sudah siap bertempur sekarang!\n");
    while(player.hp > 0 || gameStats == 0){
        stateSprt(stateCount);
        printPlayer(&player);
        
        if(!player.inCombat){
            int userLocChoice;
            printf("\nCepat! pilihlah area yang ingin kamu pertahankan sekarang!\n");
            for(int idx=0; idx<LOCATIONS_COUNT; idx++){
                printf("%d. %-16s | %.1f / %.1f (%.0f%%) | Status: %s\n",
                    idx+1, locations[idx].name, locations[idx].hp, locations[idx].maxHP, (locations[idx].hp/locations[idx].maxHP)*100, (locations[idx].enemyCount == 0) ? "Aman" : "Tidak aman");
            }
            printf("Nomor lokasi: ");
            scanf("%d", &userLocChoice);
            changeLocation(&player, --userLocChoice);
        } else {
            int locIdx = locationIdx(player);
            printf("\nLihat, ada musuh di sana! Tentukanlah mana yang ingin kamu serang!\n");
            for(int idx=0; idx<ENEMY_MAX; idx++){
                printf("%d. %-12s | HP: %5.1f | ATK: %4.1f\n", idx+1, locations[locIdx].enemy[idx].name, locations[locIdx].enemy[idx].stats.hp, locations[locIdx].enemy[idx].stats.atk);
            }
            printf("Nomor: ");
            scanf("%d", &userAtkChoice);
            damageApply(&player, locations[locIdx].enemy, --userAtkChoice);
        }
        stateCount++;
    }
    
    return 0;
}

void stateSprt(int number){
    char senSep[16] ="";
    for(int idx=0; idx<7; idx++){
        strcat(senSep, "-=");
    }
    strcat(senSep, "-");

    char finalSen[64] = "";
    char temp[16] = "";
    strcat(finalSen, senSep);
    sprintf(temp, " State ke-%d ", number);
    strcat(finalSen, temp);
    strcat(finalSen, senSep);

    printf("\n%s\n", finalSen);
}

void chooseWeapon(Player *player, Weapons w[], int size){
    stateSprt(stateCount);
    printPlayer(player);
    printf("\nSekarang ini kota Vjilandra sedang diserang! Kami membutuhkan bantuanmu segera!\nSekarang pilihlah di antara kedua senjata ini!\n");
    for(int idx=0; idx<2; idx++){
        printf("%d. %-12s (ATK: %d | Crit. Ch.: %.0f%% | Lifesteal(LS) Ch.: %.0f%%)\n",
            idx+1,
            startUpWeapons[idx].name,
            startUpWeapons[idx].atk,
            startUpWeapons[idx].critC*100,
            startUpWeapons[idx].lsC*100
        );
    }
    int userChoiceWeapon;
    printf("Nomor senjata: ");
    scanf("%d", &userChoiceWeapon);
    weaponsAffect(player, startUpWeapons[userChoiceWeapon-1]);
    stateCount++;
}

void chooseArmours(Player *player, Armours a[], int size){
    stateSprt(stateCount);
    printPlayer(player);
    printf("\nBagus! Sekarang pilihlah pakaian tempur mu!\n");
    for(int idx=0; idx<2; idx++){
        printf("%d. %-12s (HP: %3d | DEF: %3d)\n",
            idx+1,
            startUpArmours[idx].name,
            startUpArmours[idx].hp,
            startUpArmours[idx].def
        );
    }
    int userChoiceArmour;
    printf("Nomor armor: ");
    scanf("%d", &userChoiceArmour);
    armoursAffect(player, startUpArmours[userChoiceArmour-1]);
    stateCount++;
}