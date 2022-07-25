#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

int my_atoi(const char* _name){
    int walk = 0;
    int out = 0;
    while(*(_name+walk) != '\0'){
        if(*(_name+walk) >= '0' && *(_name+walk) <= '9'){
            out = (out*10)+(*(_name+walk) - '0');
        }
        walk++;
    }

    return out;
}

int isnumber(char in){
    if(in >= '0' && in <= '9'){
        return 1;
    }
    return 0;
}