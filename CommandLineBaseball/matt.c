//
//  matt.c
//  CommandLineBaseball
//
//  Created by Matthew Barber on 4/25/17.
//  Copyright © 2017 self.edu. All rights reserved.
//

#include "clb.h"
Player* team1 = NULL;
Player* team2 = NULL;
Player* endUser = NULL;
Player* endComputer = NULL;

void draft(Player draftable[], Player hash[], int arrayLength){
    
    int choice;
    int picks = 0;
    
    while(picks < 9){
        draftOptions();
        scanf("%d", &choice);
        
        while(choice < 1 || choice > 7){
            printf("Invalid choice. Options are 1 - 6\n");
            printf("Select a valid option: ");
            scanf("%d", &choice);
        }
        
        switch(choice){
                
            case 1:
                sortPlayerList(draftable, 1, arrayLength);
                break;
                
            case 2:
                sortPlayerList(draftable, 3, arrayLength);
                break;
                
            case 3:
                sortPlayerList(draftable, 2, arrayLength);
                break;
                
            case 4:
                sortPlayerList(draftable, 4, arrayLength);
                break;
                
            case 5:
                printArray(draftable, arrayLength);
                break;
            
            case 6:
                searchPlayer(hash);
                break;
                
            case 7:
                sortPlayerList(draftable, 5, arrayLength);
                pickPlayerUser(draftable, hash);
                pickPlayerComputer(draftable, hash, arrayLength);
                picks++;
                break;
        }
    }
    
    endUser->next = team1;
    endComputer->next = team2;
}

void draftOptions(void){
    
    printf("\n*** Draft Menu ****\n");
    printf("1) Sort by name\n");
    printf("2) Sort by power\n");
    printf("3) Sort by contact\n");
    printf("4) Sort by pitching\n");
    printf("5) Show players\n");
    printf("6) Search for player\n");
    printf("7) Draft a player\n");
    printf("Select an option: ");
}

void printTeam(Player* team){
    
    Player* current = team;
    
    while(1){
        printf("%d. %s %s %d %d %d\n", current->ID, current->first, current->last, current->power, current->contact, current->pitching);
        current = current->next;
        if(current == team)
            break;
    }
    
}

void pickPlayerUser(Player draftable[], Player hash[]){
    
    int id;
    printf("Enter the ID of the player you would like to draft: ");
    scanf("%d", &id);
    
    while(id < 1 || id > 50 || draftable[id].drafted == 1){
        printf("Invalid pick. Please choose a player 1 - 50 that has not been drafted: ");
        scanf("%d", &id);
    }
    
    Player *picked = malloc(sizeof(Player));
    
    *picked = draftable[id];
    
    if(team1 == NULL){
        endUser = picked;
    }
    
    picked->next = team1;
    team1 = picked;
    
    draftable[id].drafted = 1;
    hash[getHashNumber(draftable[id].last, hash)].drafted = 1;
}

void pickPlayerComputer(Player draftable[], Player hash[], int arrayLength){
    
    int i;
    int max = -1;
    int index = 0;
    
    for(i = 0; i < arrayLength; i++){
        if(draftable[i].overall > max && draftable[i].drafted != 1){
            max = draftable[i].overall;
            index = i;
        }
    }
    
    Player *picked = malloc(sizeof(Player));
    
    *picked = draftable[index];
    
    if(team2 == NULL){
        endComputer = picked;
    }
    
    picked->next = team2;
    team2 = picked;
    
    draftable[index].drafted = 1;
    hash[getHashNumber(draftable[index].last, hash)].drafted = 1;
}

int getHashNumber(char* name, Player array[]){
    
    int i;
    int key = 0;
    double a = 0.618942;
    int j;
    
    for(i = 0; name[i] != '\0'; i++){
        key += name[i] + i;
    }
    
    
    key = 100 * ((double) (key * a) - (int) (key * a));
    
    for(j = 0; array[key].last[0] != '\0' && strcmp(array[key].last, name) != 0; j++){
        key = (key + 1) % 100;
    }
    
    return key;
}

int searchPlayerHash(char* name, Player array[]){
    
    int key = getHashNumber(name, array);
    
    if(array[key].last[0] == '\0'){
        return -1;
    }
    else{
        return key;
    }
}

void searchPlayer(Player hash[]){
    
    char name[50];
    
    printf("Enter the name of the player you'd like to search: ");
    scanf("%s", name);
    int key = searchPlayerHash(name, hash);
    if(key == -1 || hash[key].drafted == 1){
        printf("%s is not a draftable player\n", name);
    }
    else{
        printf("%d. %s %s %d %d %d\n", hash[key].ID, hash[key].first, hash[key].last, hash[key].power, hash[key].contact,hash[key].pitching);
    }
}

Player* getUserTeam(void){
    
    return team1;
}

Player* getComputerTeam(void){
    
    return team2;
}

int determineHit(Player batter, Player pitcher){
    
    if(rand() % (batter.contact + 2) < rand() % (pitcher.pitching + 2)){
        return -1;
    }
    
    double chance = batter.power / 10;
    int bases = (rand() % 10) * chance;
    
    switch(bases){
            
        case 0: case 1: case 2: bases = 1;
            break;
        case 3: case 4: bases = 2;
            break;
        case 5: case 6: case 7: bases = 3;
            break;
        case 8: case 9: case 10: bases = 4;
            break;
    }
    
    return bases;
}





