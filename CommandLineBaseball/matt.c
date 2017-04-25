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
            
            
    }
    
    
}

void draftOptions(void){
    
    printf("1) Sort by name\n");
    printf("2) Sort by contact\n");
    printf("3) Sort by power\n");
    printf("4) Sort by pitching\n");
    printf("5) Show players\n");
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
    
    Player *picked = malloc(sizeof(Player));
    
    *picked = draftable[id];
    
    picked->next = team1;
    team1 = picked;
    
    draftable[id].drafted = 1;
    return draftable;
}

Player* pickPlayerComputer(Player draftable[]){
    
    
    
}





