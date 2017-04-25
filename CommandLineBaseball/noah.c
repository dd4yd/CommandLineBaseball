//
//  noah.c
//  CommandLineBaseball
//
//  Created by Noah Panicola on 4/25/17.
//  Copyright © 2017 self.edu. All rights reserved.
//

#include "clb.h"

Player *populate(char *filename){
    
    int i = 0;
    
    FILE *fp = NULL;
    fp = fopen(filename, "r");
    
    //return NULL if the file could not be read
    if(!fp){
        printf("The file could not be read.\n");
        return NULL;
    }
    
    //gets the correct amount of players
    arrayLength = getLength(fp);
    Player list[arrayLength];
    
    //populate array
    for(i=0; i < arrayLength; i++){
        fscanf(fp, "%s %s %d %d %d", list[i].first, list[i].last, &list[i].power, &list[i].contact, &list[i].pitching);
        list[i].drafted = 0;
        list[i].ID = i;
        list[i].next = NULL;
    }
    
    return list;
    
}

int getLength(FILE *fp){
    
    int lines = 0;
    int ch = 0;
    
    while(!feof(fp)){
        ch = fgetc(fp);
        if(ch == '\n'){
            lines++;
        }
    }
    return lines;
}

void printArray(Player a[]){
    int i = 0;
    printf("ID\tFirst\tLast\tPower\tContact\tPitching");
    for(i=0; i < arrayLength; i++){
        if(a[i].drafted == 0){
            printf("%d\t%s\t%s\t%d\t%d\t%d\t\n", a[i].ID, a[i].first, a[i].last, a[i].power, a[i].contact, a[i].pitching);
        }
    }
}




