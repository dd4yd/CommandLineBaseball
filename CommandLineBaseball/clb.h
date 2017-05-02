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
    int overall;
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
Player *team1, *team2;
int arrayLength;

//noah's prototypes
void populate(char *filename, Player list[]);
int getLength(char *filename);
void printArray(Player a[]);

//Matt's prototypes
Player* draft(Player draftable[]);
void draftOptions(void);
void printTeam(Player* team);
Player* pickPlayerUser(Player draftable[]);
Player* pickPlayerComputer(Player draftable[]);

//David's prototypes
Player* sortPlayerList(Player list[], int n, int field);
void downheap(Player list[], int n, int i, int field);
int maxIndex(Player list[], int n, int i, int j, int k, int field);
