//
//  david.c
//  CommandLineBaseball
//
//  Created by David Dean on 4/25/17.
//  Copyright © 2017 self.edu. All rights reserved.
//

#include "clb.h"

//NEED max index func
//NEED downheap func
//NEED heapsort func

int maxIndex(Player list[], int n, int i, int j, int k, int field){
    //field: 1->contact, 2->power, 3->pitching, 4->name
    int max = i;
    switch(field){
        case 1: //last name
            if(j < n && strcmp(list[j].last, list[max].last) > 0){
                max = j;
            }
            if(k < n && strcmp(list[k].last, list[max].last) > 0){
                max = k;
            }
            break;
        case 2: //contact
            if(j < n && list[j].contact < list[max].contact){
                max = j;
            }
            if(k < n && list[k].contact < list[max].contact){
                max = k;
            }
            break;
        case 3: //power
            if(j < n && list[j].power < list[max].power){
                max = j;
            }
            if(k < n && list[k].power < list[max].power){
                max = k;
            }
            break;
        case 4: //pitching
            if(j < n && list[j].pitching < list[max].pitching){
                max = j;
            }
            if(k < n && list[k].pitching < list[max].pitching){
                max = k;
            }
            break;
        case 5: //ID
            if(j < n && list[j].ID > list[max].ID){
                max = j;
            }
            if(k < n && list[k].ID > list[max].ID){
                max = k;
            }
            break;
        default:
            max = i;
            break;
    }
    return max;
}

void downheap(Player list[], int n, int i, int field){
    while(1){
        int j = maxIndex(list, n, i, 2*i+1, 2*i+2, field);
        if(j == i) break;
        
        Player player = list[i];
        list[i] = list[j];
        list[j] = player;
        i = j;
    }
}

void sortPlayerList(Player list[], int field, int arrayLength){
    
    //field: 1->name, 2->contact, 3->power, 4->pitching
    int i;
    for(i = (arrayLength-2)/2; i >= 0; i--){
        downheap(list, arrayLength, i, field);
    }
    for(i = 0; i < arrayLength; i++){
        Player player = list[arrayLength-1-i];
        list[arrayLength-i-1] = list[0];
        list[0] = player;
        downheap(list, arrayLength-i-1, 0, field);
    }
}

void printScoreboard(Game game){

    int i;
    
    printf("-----------------------------\n");
    printf("|                           |\n");
    printf("|---COMMAND LINE BASEBALL---|\n");
    printf("|                           |\n");
    printf("| Team 1:                   |\n| ");
    for(i = 0; i < 18; i+=2){ //TEAM 1 SCORE
        printf("%d ", game.scoreboard[i]);
    }
    printf("\n| Team 2:                   |\n| ");
    for(i = 1; i < 18; i+=2){
        printf("%d ", game.scoreboard[i]);
    }
    printf("\n|                           |\n");
    printf("| Team 1 Total: %d           |\n", game.user_score);
    printf("| Team 2 Total: %d           |\n", game.cpu_score);
    printf("-----------------------------\n");

}

void printDiamond(Game game){

    char first, second, third, home;

    if(game.bases[1] == 1) first = 'X';
    else first = 'O';
    if(game.bases[2] == 2) second = 'X';
    else second = 'O';
    if(game.bases[3] == 3) third = 'X';
    else third = 'O';
    home = 'O';

    printf("==============================\n");
    printf("              %c              \n", second);
    printf("             / \\             \n");
    printf("            /   \\            \n");
    printf("           /     \\           \n");
    printf("          /       \\          \n");
    printf("         /         \\         \n");
    printf("        /           \\        \n");
    printf("       /             \\       \n");
    printf("      /               \\      \n");
    printf("     /                 \\     \n");
    printf("    /                   \\    \n");
    printf("   /                     \\   \n");
    printf("  /                       \\  \n");
    printf(" /                         \\ \n");
    printf("%c                           %c\n", third, first);
    printf(" \\                          /\n");
    printf("  \\                        / \n");
    printf("   \\                      /  \n");
    printf("    \\                    /   \n");
    printf("     \\                  /    \n");
    printf("      \\                /     \n");
    printf("       \\              /      \n");
    printf("        \\            /       \n");
    printf("         \\          /        \n");
    printf("          \\        /         \n");
    printf("           \\      /          \n");
    printf("            \\    /           \n");
    printf("             \\  /            \n");
    printf("              %c              \n", home);
    printf("==============================\n");

}

void printCount(Game game){
    printf("  --------------------  ");
    printf("  |Balls Strikes Outs|  \n");
    printf("  |  %d      %d     %d  |\n", game.balls, game.strikes, game.outs);
    printf("  --------------------  \n");
}

void writeGameToFile(Game game){

    char *filename = "saveFile.txt";
    FILE *fPtr = fopen(filename, "w");
    if(fPtr == NULL){
        printf("Couldn't open saveFile.txt\n");
    }

    int i;
    int teamSize = 9;
    int scoreboardSize = 18;
    int bases = 4;

    fprintf(fPtr, "Team 1:\n");
    for(i = 0; i < teamSize; i++){
        fprintf(fPtr, "%d %s %s %d %d %d\n", game.team1[i].ID, game.team1[i].first, game.team1[i].last, game.team1[i].power, game.team1[i].contact, game.team1[i].pitching);
    }
    fprintf(fPtr, "\nTeam 2:\n");
    for(i = 0; i < teamSize; i++){
        fprintf(fPtr, "%d %s %s %d %d %d\n", game.team2[i].ID, game.team2[i].first, game.team2[i].last, game.team2[i].power, game.team2[i].contact, game.team2[i].pitching);
    }

    fprintf(fPtr, "\nScoreboard:\n");
    fprintf(fPtr, "Team 1: ");
    for(i = 0; i < scoreboardSize; i+=2){
        fprintf(fPtr, "%d ", game.scoreboard[i]);
    }
    fprintf(fPtr, "\nTeam 2: ");
    for(i = 1; i < scoreboardSize; i+=2){
        fprintf(fPtr, "%d ", game.scoreboard[i]);
    }

    fprintf(fPtr, "\nInning: %d\n", game.inning);
    fprintf(fPtr, "Balls: %d\n", game.balls);
    fprintf(fPtr, "Strikes: %d\n", game.strikes);
    fprintf(fPtr, "Ours: %d\n", game.outs);

    fprintf(fPtr, "\n Bases (home, 1st, 2nd, 3rd): ");
    for(i = 0; i < bases; i++){
        fprintf(fPtr, "%d ", game.bases[i]);
    }

    fprintf(fPtr, "\nCPU Pitcher:\n");
    fprintf(fPtr, "%d %s %s %d %d %d\n", game.cpu_pitcher->ID, game.cpu_pitcher->first, game.cpu_pitcher->last, game.cpu_pitcher->power, game.cpu_pitcher->contact, game.cpu_pitcher->pitching);
    fprintf(fPtr, "\nUser Pitcher:\n");
    fprintf(fPtr, "%d %s %s %d %d %d\n", game.user_pitcher->ID, game.user_pitcher->first, game.user_pitcher->last, game.user_pitcher->power, game.user_pitcher->contact, game.user_pitcher->pitching);

    fclose(fPtr);

}

