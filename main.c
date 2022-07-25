#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lib/path_lib.h"

void free_map(map_struct* map){
    for(int i = 0; i < map->sizex; i++){
        free(map->map[i]);
        free(map->visited[i]);
    }
    free(map->map);
    free(map->visited);
    free(map);
}

int main(int ARGC, char** ARGV){
    if(ARGC == 1){
        printf("Please provide a valid map file\n");
        return 0;
    }
    map_struct* map = load_map(ARGV[1]);
    if(map == NULL){
        return 0;
    }

    path* final = bfs_pathfind(map);

    if(final != NULL){
        printresult(final, map);
        free(final->history);
        free(final);
    }

    free_map(map);

    return 0;
}