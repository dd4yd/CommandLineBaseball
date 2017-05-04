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
    int inning;
    int scoreboard[18];
    int outs;
    int strikes;
    int balls;
    int cpu_pitcher;
    int user_pitcher;
    int bases[4];
    
} Game;

//noah's prototypes
void populate(char *filename, Player list[], Player arrayHash[], int arrayLength);
int getLength(char *filename);
void printArray(Player a[], int arrayLength);
Game startGame(Player *team1, Player *team2);
Game playGame(Game game);
void bat(Game *game);
void advanceRunner(Game *game);
Player* getTeam(Game *game);

//Matt's prototypes
void draft(Player draftable[], Player hash[], int arrayLength);
void draftOptions(void);
void printTeam(Player* team);
void pickPlayerUser(Player draftable[], Player hash[]);
void pickPlayerComputer(Player draftable[], Player hash[], int arrayLength);
int searchPlayerHash(char* name, Player array[]);
int getHashNumber(char* name, Player array[]);
Player* getComputerTeam(void);
Player* getUserTeam(void);
void searchPlayer(Player hash[]);

//David's prototypes
void sortPlayerList(Player list[], int field, int arrayLength);
void downheap(Player list[], int n, int i, int field);
int maxIndex(Player list[], int n, int i, int j, int k, int field);
