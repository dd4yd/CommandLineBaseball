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
        
        while(choice < 1 || choice > 9){
            printf("Invalid choice. Options are 1 - 9\n");
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
                printf("\n--- Draftable Players ---\n");
                printArray(draftable, arrayLength);
                break;
                
            case 6:
                printf("\n--- USER TEAM ---\n");
                printTeam(team1);
                break;
                
            case 7:
                printf("\n--- COMPUTER TEAM ---\n");
                printTeam(team2);
                break;
            
            case 8:
                searchPlayer(hash);
                break;
                
            case 9:
                sortPlayerList(draftable, 5, arrayLength);
                pickPlayerUser(draftable, hash, arrayLength);
                pickPlayerComputer(draftable, hash, arrayLength);
                picks++;
                break;
                
            default:
                printf("Error\n");
                break;
        }
    }
    
    endUser->next = team1;
    endComputer->next = team2;
}

void draftOptions(void){
    
    printf("\n--- Draft Menu ---\n");
    printf("1) Sort by name\n");
    printf("2) Sort by power\n");
    printf("3) Sort by contact\n");
    printf("4) Sort by pitching\n");
    printf("5) Show draftable players\n");
    printf("6) Show user team\n");
    printf("7) Show computer team\n");
    printf("8) Search for player\n");
    printf("9) Draft a player\n");
    printf("Select an option: ");
}

void printTeam(Player* team){
    
    if(team == NULL){
        printf("No one is on the team\n");
        return;
    }
    
    Player* current = team;
    
    while(1){
        printf("%d. %s %s %d %d %d\n", current->ID, current->first, current->last, current->power, current->contact, current->pitching);
        current = current->next;
        if(current == team)
            break;
    }
    
}

void pickPlayerUser(Player draftable[], Player hash[], int arrayLength){
    
    int id;
    printf("Enter the ID of the player you would like to draft: ");
    scanf("%d", &id);
    
    while(id < 0 || id > arrayLength || draftable[id].drafted == 1){
        printf("Invalid pick. Please choose a player 0 - %d that has not been drafted: ", arrayLength);
        scanf("%d", &id);
    }
    
    Player *picked = malloc(sizeof(Player));
    
    *picked = draftable[id];
    
    if(team1 == NULL){
        endUser = picked;
    }
    
    picked->next = team1;
    team1 = picked;
    endUser->next = team1;
    
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
    endComputer->next = team2;
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

AtBat determineHit(Player batter, Player pitcher){
    
    if(rand() % (batter.contact + 2) < rand() % (pitcher.pitching + 2)){
        if(batter.contact > batter.power) return GROUNDOUT;
        else return FLYOUT;
    }
    
    double chance = (double) batter.power / 10;
    int bases = (rand() % 10) * chance + rand() % 3;
    
            
    if(bases <= 2)
        return SINGLE;
    if(bases <= 4)
        return DOUBLE;
    if(bases <= 7)
        return TRIPLE;
    if(bases <= 11)
        return HOMERUN;
    
    return FLYOUT;
}

Game loadGame(char* filename){
    
    FILE* fPtr = fopen(filename, "w");
    
    Game game;
    
    if(fPtr == NULL){
        printf("File could not be opened\n");
        return game;
    }
    
    char temp[50];
    int i;
    int teamSize = 9;
    int scoreboardSize = 18;
    int bases = 4;
    
    while (fgets(temp, sizeof(temp), fPtr)){
    }
    for(i = 0; i < teamSize; i++){
        fscanf(fPtr, "%d %s %s %d %d %d", &game.team1[i].ID, game.team1[i].first, game.team1[i].last, &game.team1[i].power, &game.team1[i].contact, &game.team1[i].pitching);
    }
    
    while (fgets(temp, sizeof(temp), fPtr)){
    }
    for(i = 0; i < teamSize; i++){
        fscanf(fPtr, "%d %s %s %d %d %d", &game.team2[i].ID, game.team2[i].first, game.team2[i].last, &game.team2[i].power, &game.team2[i].contact, &game.team2[i].pitching);
    }
    
    while (fgets(temp, sizeof(temp), fPtr)){
    }
    while (fgets(temp, sizeof(temp), fPtr)){
    }
    for(i = 0; i < scoreboardSize; i+=2){
        game.scoreboard[i] = fgetc(fPtr);
    }
    
    while (fgets(temp, sizeof(temp), fPtr)){
    }
    for(i = 1; i < scoreboardSize; i+=2){
        game.scoreboard[i] = fgetc(fPtr);
    }
    
    fscanf(fPtr, "%s %d", temp, &game.inning);
    fscanf(fPtr, "%s %d", temp, &game.balls);
    fscanf(fPtr, "%s %d", temp, &game.strikes);
    fscanf(fPtr, "%s %d", temp, &game.outs);
    
    while (fgets(temp, sizeof(temp), fPtr)){
    }
    for(i = 0; i < bases; i++){
        game.bases[i] = fgetc(fPtr);
    }
    
    while (fgets(temp, sizeof(temp), fPtr)){
    }
    fscanf(fPtr, "%d %s %s %d %d %d", &game.cpu_pitcher->ID, game.cpu_pitcher->first, game.cpu_pitcher->last, &game.cpu_pitcher->power, &game.cpu_pitcher->contact, &game.cpu_pitcher->pitching);
    while (fgets(temp, sizeof(temp), fPtr)){
    }
    fscanf(fPtr, "%d %s %s %d %d %d", &game.user_pitcher->ID, game.user_pitcher->first, game.user_pitcher->last, &game.user_pitcher->power, &game.user_pitcher->contact, &game.user_pitcher->pitching);
    
    fclose(fPtr);

    return game;
}

void simInning(Game *game){
    
    int num = rand() % game->user_pitcher->pitching;
    
    if(num >= 3){
        game->scoreboard[game->inning - 1] = 0;
        printf("%s pitched in inning %d.\nThe computer team had %d hits and 0 runs\n", game->user_pitcher->last, game->inning/2, rand() % 3);
        return;
    }
    if(num >= 2){
        game->scoreboard[game->inning - 1] = 1;
        game->cpu_score += 1;
        printf("%s pitched in inning %d.\nThe computer team had %d hits and 1 run\n", game->user_pitcher->last, game->inning/2, rand() % 3 + 1);
        return;
    }
    if(num >= 1){
        game->scoreboard[game->inning - 1] = 2;
        game->cpu_score += 2;
        printf("%s pitched in inning %d.\nThe computer team had %d hits and 2 runs\n", game->user_pitcher->last, game->inning/2, rand() % 4 + 1);
        return;
    }
    if(num >= 0){
        game->scoreboard[game->inning - 1] = 3;
        game->cpu_score += 3;
        printf("%s pitched in inning %d.\nThe computer team had %d hits and 3 runs\n", game->user_pitcher->last, game->inning/2, rand() % 5 + 2);
        return;
    }
}


void freeTeam(Player* team){
    
    Player* start = team->next;
    Player* previous = NULL;
    team->next = NULL;
    
    while(start != NULL){
        previous = start;
        start = start->next;
        free(previous);
    }
}




