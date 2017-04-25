//
//  noah.c
//  CommandLineBaseball
//
//  Created by Noah Panicola on 4/25/17.
//  Copyright © 2017 self.edu. All rights reserved.
//

#include <stdio.h>

Player *populate(char *filename){
    
    int i = 0;
    Player list[50]
    
    //gets the correct amount of players
    int length = getLength();
    
    FILE *fp = NULL;
    fp = fopen(filename, "r");
    
    //return NULL if the file could not be read
    if(!fp){
        printf("The file could not be read.\n");
        return NULL;
    }
    
}

int getLength(char *filename, FILE *fp){
    
    int lines = 0;
    int ch = 0;
    
    while(!feof(fp))
    {
        ch = fgetc(fp);
        if(ch == '\n')
        {
            lines++;
        }
    }
    
    return lines;
}
