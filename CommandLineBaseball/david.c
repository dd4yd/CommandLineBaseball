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
        case 1:
            if(j < n && list[j].contact > list[max].contact){
                max = j;
            }
            if(k < n && list[k].contact > list[max].contact){
                max = k;
            }
            break;
        case 2:
            if(j < n && list[j].power > list[max].power){
                max = j;
            }
            if(k < n && list[k].power > list[max].power){
                max = k;
            }
            break;
        case 3:
            if(j < n && list[j].pitching > list[max].pitching){
                max = j;
            }
            if(k < n && list[k].pitching > list[max].pitching){
                max = k;
            }
            break;
        case 4: //sort by last name only
            if(j < n && strcmp(list[j].last, list[max].last) > 0){
                max = j;
            }
            if(k < n && strcmp(list[k].last, list[max].last) > 0){
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
        
        Player person = list[i];
        list[i] = list[j];
        list[j] = person;
        i = j;
    }
}

Player* sortPlayerList(Player list[], int n, int field){
    
    //field: 1->contact, 2->power, 3->pitching, 4->name
    
}

