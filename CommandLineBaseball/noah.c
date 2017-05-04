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
        arrayHash[key].pitching = list[i].pitching;
        arrayHash[key].contact = list[i].contact;
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
    printf("ID First Last Power Contact Pitching\n\n");
    for(i=0; i < arrayLength; i++){
        if(a[i].drafted == 0){
            printf("%d %s %s %d %d %d\n", a[i].ID, a[i].first, a[i].last, a[i].power, a[i].contact, a[i].pitching);
        }
    }
}

Game* newGame(Player *team1, Player *team2){
    
    if(team1 == NULL || team2 == NULL){
        printf("Team values are null.\nTerminating program...\n");
        exit(-1);
    }
    
    Game *game = malloc(sizeof(Game));
    int i = 0;
    
    game->balls = 0;
    game->outs = 0;
    game->strikes = 0;
    game->inning = 1;
    game->user_score = 0;
    game->cpu_score = 0;
    
    game->team1 = team1;
    game->team2 = team2;
    game->next = NULL;
    
    for(i=0; i < 18; i++){ game->scoreboard[i] = 0; }
    for(i=0; i < 4; i++){ game->bases[i] = 0; }
    
    game->cpu_pitcher = getHighestPitcher(team2);
    game->user_pitcher = getHighestPitcher(team1);
    
    return game;
}

Game* playGame(Game *game){
    
    AtBat at_bat;
    
    while(game->inning <= 18){
        
        while(game->outs != 3){
            
            //user bats
            at_bat = user_bat(game);
            
            if(at_bat == WALK || at_bat == SINGLE){
                printf("%s %s hit a single!\n", game->team1->first, game->team1->last);
                advanceRunner(game, 1);
            } else if (at_bat == DOUBLE){
                printf("%s %s hit a double!\n", game->team1->first, game->team1->last);
                advanceRunner(game, 2);
            } else if (at_bat == TRIPLE){
                printf("%s %s hit a triple!\n", game->team1->first, game->team1->last);
                advanceRunner(game, 3);
            } else if (at_bat == HOMERUN){
                printf("%s %s hit a homerun!\n", game->team1->first, game->team1->last);
                advanceRunner(game, 4);
            } else if (at_bat == FLYOUT){
                printf("%s %s flew out.\n", game->team1->first, game->team1->last);
                game->outs = game->outs + 1;
            } else if (at_bat == GROUNDOUT){
                printf("%s %s grounded out.\n", game->team1->first, game->team1->last);
                game->outs++;
            } else if (at_bat == STRIKEOUT){
                printf("%s %s struck out.\n", game->team1->first, game->team1->last);
                game->outs++;
            }
            printf("------------------------------------------\n");
            
            //reset count
            game->balls = 0;
            game->strikes = 0;
            
            //print diamond
            printDiamond(*game);
            
            //increment the batter
            game->team1 = game->team1->next;
        }
        
        //sim cpu inning
        game->inning++;
        simInning(game);
        
        //print scoreboard
        printScoreboard(*game);
        
        //go to the next inning
        nextInning(game);
    }
    
    return game;
}

AtBat user_bat(Game *game){
    
    AtBat hit;
    int guess, pitch;
    
    printf("------------------------------------------\n");
    printf("Pitcher: %s %s\nBatter: %s %s\n", game->cpu_pitcher->first, game->cpu_pitcher->last, game->team1->first, game->team1->last);
    
    while(1){
        
        //check for walk and strikeout
        if(game->balls == 4) {
            return WALK;
        } else if(game->strikes == 3) {
            return STRIKEOUT;
        }
        
        //print at bat
        printf("------------------------------------------\n");
        printf("Select a pitch to hit (1-4): ");
        
        //get guess and pitch
        scanf("%d", &guess);
        pitch = (rand() % 5) + 1;
        
        if(pitch == 5){
            game->balls++;
        } else if(guess == pitch){
            hit = determineHit(*(game->team1), *(game->cpu_pitcher));
            return hit;
        } else {
            game->strikes++;
        }
        printCount(*game);
    }
}

void nextInning(Game *game){
    
    game->inning++;
    
    if((game->inning + 1)/2 < 10){
       printf("We are moving to inning %d.\n", (game->inning + 1)/2); 
    }
    
    game->outs = 0;
    game->balls = 0;
    game->strikes = 0;
    
    int i = 0;
    for(i=0; i < 4; i++){
        game->bases[i] = 0;
    }
    
}


Player* getHighestPitcher(Player *team){
    
    Player *head = team;
    Player *max = team;
    
    while(1){
        
        if(team->pitching > max->pitching){
            max = team;
        }
        
        team = team->next;
        if(team == head) break;
    }
    
    return max;
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

void advanceRunner(Game *game, int hit){
    
    int i = 0;
    
    if(game->bases[1] == 0 && hit == 1){
        game->bases[1] = 1;
        return;
    }
    
    for(i=3; i >= 0; i--){
        if(game->bases[i] != 0){
            game->bases[i] += hit;
            game->bases[i + hit] = game->bases[i];
        }
        if(game->bases[i] >= 4){
            game->user_score++;
            game->scoreboard[game->inning - 1]++;
            game->bases[i] = 0;
        } else {
            game->bases[i + hit] = game->bases[i];
            game->bases[hit] = hit;
        }
    }
    
    if(hit == 4) {
        game->scoreboard[game->inning - 1]++;
        game->user_score++;
    }
    
    /*printf("Bases: ");
    for(i=0; i < 4; i++){
        printf("%d ",game->bases[i]);
    }
    printf("\n");*/
    
}
