//
//  main.c
//  CommandLineBaseball
//
//  Created by Noah Panicola on 4/25/17.
//  Copyright © 2017 self.edu. All rights reserved.
//

#include "clb.h"

int main(int argc, const char * argv[]) {
    
    //gets array length and sets global variable
    int arrayLength = getLength("playerlist.txt");
    
    //populates the player list
    Player list[arrayLength];
    populate("playerlist.txt", list, arrayLength);
    
    //debug
    printArray(list, arrayLength);
    
}
