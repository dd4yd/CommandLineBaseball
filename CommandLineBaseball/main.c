//
//  main.c
//  CommandLineBaseball
//
//  Created by Noah Panicola on 4/25/17.
//  Copyright © 2017 self.edu. All rights reserved.
//

#include "clb.h"

int main(int argc, char * argv[]) {
    
    if(argc != 2){
        printf("Invalid amount of arguments.\n"
               "Correct usage: ./(program name) (input file)\n");
        return 0;
    }
    
    
    printf("***** COMMAND LINE BASEBALL *****\n");
    printf("---------------------------------\n\n");
    
    time_t t;
    srand((unsigned) time(&t));
    
    //gets array length and sets global variable
    int arrayLength = getLength(argv[1]);
    
    //populates the player list
    Player list[arrayLength];
    Player hash[100];
    
    populate(argv[1], list, hash, arrayLength);
    
    //debug
    printArray(list, arrayLength);
    
    printf("\n--------------------------------------------\n");
    
    draft(list, hash, arrayLength);
    Player* userTeam = getUserTeam();
    Player* computerTeam = getComputerTeam();
    printf("\n--- USER TEAM ---\n");
    printTeam(userTeam);
    printf("\n--- COMPUTER TEAM ---\n");
    printTeam(computerTeam);
    
    Game *game = NULL;
    game = newGame(userTeam, computerTeam);
    playGame(game);
    free(game);
    freeTeam(userTeam);
    freeTeam(computerTeam);
    
    printf("\n\nThanks for playing Command Line Baseball.\n");
    printf("Authors: Matt Barber, David Dean, Noah Panicola\n\n");
    
    return 0;
}
