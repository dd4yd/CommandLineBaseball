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
            if(j < n && list[j].ID < list[max].ID){
                max = j;
            }
            if(k < n && list[k].ID < list[max].ID){
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
    int sum1 = 0;
    int sum2 = 0;

    printf("-----------------------------\n");
    printf("|                           |\n");
    printf("|---COMMAND LINE BASEBALL---|\n");
    printf("|                           |\n");
    for(i = 0; i < 18; i+2){ //TEAM 1 SCORE
        sum1 += game.scoreboard[i];
        printf("| Team 1: %d ", game.scoreboard[i]);
    }
    printf("|\n");
    for(i = 1; i < 18; i+2){
        sum1 += game.scoreboard[i];
        printf("| Team 2: %d ", game.scoreboard[i]);
    }
    printf("|\n");
    printf("|                           |\n");
    printf("| Team 1 Total: %d           |\n", sum1);
    printf("| Team 2 Total: %d           |\n", sum2);
    printf("-----------------------------\n");

}

void printDiamond(Game game){

    int i;
    char first, second, third, home;

    if(game.bases[1] == 1) first = 'X';
    else first = 'O';
    if(game.bases[2] == 1) second = 'X';
    else second = 'O';
    if(game.bases[3] == 3) third = 'X';
    else third = 'O';

    home = 'O';
    printf(" --------------------\n");
    printf(" |Balls Strikes Outs|\n");
    printf(" | %d      %d     %d   |\n" game.balls, game.strikes, game.outs);
    printf(" --------------------\n\n");
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

}


