//
//  noah.c
//  CommandLineBaseball
//
//  Created by Noah Panicola on 4/25/17.
//  Copyright © 2017 self.edu. All rights reserved.
//

#include "clb.h"

void populate(char *filename, Player list[], Player arrayHash[], int arrayLength){
    
    int i = 0;
    int key;
    
    FILE *fp = NULL;
    fp = fopen(filename, "r");
    
    //return NULL if the file could not be read
    if(!fp){
        printf("The file could not be read.\n");
        return;
    }
    
    //populate array
    for(i=0; i < arrayLength; i++){
        fscanf(fp, "%s %s %d %d %d", list[i].first, list[i].last, &list[i].power, &list[i].contact, &list[i].pitching);
        key = getHashNumber(list[i].last, arrayHash);
        strcpy(arrayHash[key].first, list[i].first);
        strcpy(arrayHash[key].last, list[i].last);
        arrayHash[key].power = list[i].power;
        arrayHash[key].contact = list[i].pitching;
        arrayHash[key].drafted = 0;
        arrayHash[key].ID = i;
        arrayHash[key].next = NULL;
        arrayHash[key].overall = (list[i].power + list[i].contact + list[i].pitching) / 3;
        list[i].drafted = 0;
        list[i].ID = i;
        list[i].next = NULL;
        list[i].overall = (list[i].power + list[i].contact + list[i].pitching) / 3;
    }
    fclose(fp);
}

int getLength(char *filename){
    
    FILE *fp = fopen(filename, "r");
    
    //return NULL if the file could not be read
    if(!fp){
        printf("The file could not be read.\n");
        return 0;
    }

    int lines = 0;
    int ch = 0;
    
    while(!feof(fp)){
        ch = fgetc(fp);
        if(ch == '\n'){
            lines++;
        }
    }
    
    fclose(fp);
    return lines;
}

void printArray(Player a[], int arrayLength){
    int i = 0;
    printf("ID First Last Power Contact Pitching\n");
    for(i=0; i < arrayLength; i++){
        if(a[i].drafted == 0){
            printf("%d %s %s %d %d %d\n", a[i].ID, a[i].first, a[i].last, a[i].power, a[i].contact, a[i].pitching);
        }
    }
}

Game startGame(Player *team1, Player *team2){
    
    Game game;
    
    game.balls = 0;
    game.outs = 0;
    game.strikes = 0;
    game.inning = 0;
    
    game.team1 = team1;
    game.team2 = team2;
    
    return game;
}

Game playGame(Game game){
    
    while(game.inning <= 18){
        
        while(game.outs != 3){
            bat(&game);
        }
        
        game.inning ++;
    }
    
    return game;
}

void bat(Game *game){
    
    Player *team;
    team = getTeam(game);
    
    while(game->balls < 4 && game->strikes < 3){
        
    }
}

Player* getTeam(Game *game){
    
    Player *team;
    
    if(game->inning % 2 == 0){
        team = game->team2;
    } else {
        team = game->team1;
    }
    
    return team;
}
