//libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

//structs
typedef struct player {
    char name[100];
    int power;
    int contact;
    int pitching;
    struct player *next;
} Player;

typdef struct game {
    Player *team1;
    Player *team2;
    int scoreboard[18];
    int outs;
    int strikes;
    int balls;
    int bases[4];
    
} Game;

//prototypes go here
