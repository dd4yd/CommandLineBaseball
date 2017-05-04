//
//  matt.c
//  CommandLineBaseball
//
//  Created by Matthew Barber on 4/25/17.
//  Copyright © 2017 self.edu. All rights reserved.
//

#include "clb.h"

Player* draft(Player draftable[]){
    
    int choice;
    int picks = 0;
    
    while(picks < 9){
        draftOptions();
        scanf("%d", &choice);
        
        while(choice < 1 || choice > 6){
            printf("Invalid choice. Options are 1 - 6\n");
            printf("Select a valid option: ");
            scanf("%d", &choice);
        }
        
        switch(choice){
                
            case 1:
                draftable = sortPlayerList(draftable, 1);
                break;
                
            case 2:
                draftable = sortPlayerList(draftable, 2);
                break;
                
            case 3:
                draftable = sortPlayerList(draftable, 3);
                break;
                
            case 4:
                draftable = sortPlayerList(draftable, 4);
                break;
                
            case 5:
                printArray(draftable);
                break;
                
            case 6:
                draftable = pickPlayerUser(draftable);
                draftable = pickPlayerComputer(draftable);
                picks++;
                break;
        }
    }
    return draftable;
}

void draftOptions(void){
    
    printf("1) Sort by name\n");
    printf("2) Sort by contact\n");
    printf("3) Sort by power\n");
    printf("4) Sort by pitching\n");
    printf("5) Show players\n");
    printf("6) Search for player\n");
    printf("6) Draft a player\n");
    printf("Select an option: ");
}

void printTeam(Player* team){
    
    Player* current = team;
    
    while(current != NULL){
        printf("%d. %s %s %d %d %d\n", current->ID, current->first, current->last, current->contact, current->power, current->pitching);
        current = current->next;
    }
}

Player* pickPlayerUser(Player draftable[]){
    
    int id;
    printf("Enter the ID of the player you would like to draft: ");
    scanf("%d", &id);
    
    while(id < 1 || id > 50 || draftable[id].drafted == 1){
        printf("Invalid pick. Please choose a player 1 - 50 that has not been drafted: ");
        scanf("%d", &id);
    }
    
    Player *picked = malloc(sizeof(Player));
    
    *picked = draftable[id];
    
    picked->next = team1;
    team1 = picked;
    
    draftable[id].drafted = 1;
    return draftable;
}

Player* pickPlayerComputer(Player draftable[]){
    
    int i;
    int max = -1;
    int index = 0;
    
    for(i = 0; i < arrayLength; i++){
        if(draftable[i].overall > max){
            max = draftable[i].overall;
            index = i;
        }
    }
    
    Player *picked = malloc(sizeof(Player));
    
    *picked = draftable[index];
    
    picked->next = team2;
    team2 = picked;
    
    draftable[index].drafted = 1;
    return draftable;
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
    
    for(j = 0; array[key].last != NULL && strcmp(array[key].last, name) != 0; j++){
        key = (key + 1) % 100;
    }
    
    return key;
}

int searchPlayerHash(char* name, Player array[]){
    
    int key = getHashNumber(name, array);
    
    if(array[key].last == NULL){
        return -1;
    }
    else{
        return key;
    }
}






