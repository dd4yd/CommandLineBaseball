//libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

//structs
typedef struct player {
    int ID;
    char first[50];
    char last[50];
    int power;
    int contact;
    int pitching;
    int drafted;
    struct player *next;
} Player;

typedef struct game {
    Player *team1;
    Player *team2;
    int scoreboard[18];
    int outs;
    int strikes;
    int balls;
    int bases[4];
    
} Game;

//global variables
Player list[50];
Player *team1, *team2;

//prototypes
