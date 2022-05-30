#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <string.h>
#include "queue_lib.h"
#include "path_lib.h"
#include "strings.h"


bool load_map_info(char* info, map_struct* map){
    int i = 0;
    int x = 0;
    char buf[16];

    //get map sizes
    while(info[i] != 'x' && i < MAP_INFOSIZE && info[i] != '\0' && info[i] != '\n'){
        if(!isnumber(info[i])){
            return false;
        }
        buf[x] = info[i];
        i++;
        x++;
        buf[x] = '\0';
    }
    map->sizex = my_atoi(buf);
    x = 0;
    i++;
    
    while(info[i] != '\n' && i < MAP_INFOSIZE){
        if(!isnumber(info[i])){
            break;
        }
        
        buf[x] = info[i];
        i++;
        x++;
        buf[x] = '\0';
    }
    map->sizey = my_atoi(buf);
    if(map->sizey < 3 || map->sizex < 3){
        return false;
    }

    map->wall = info[i];
    i++;
    map->empty = info[i];
    i++;
    map->path = info[i];
    i++;
    map->entry = info[i];
    i++;
    map->exit = info[i];

    return true;
}

map_struct* load_map(char* _path){
    struct stat st;
    FILE* file;
    map_struct* map = malloc(sizeof(map_struct));

    if (stat(_path, &st) == -1) {
        printf("No map found\n");
        free(map);
        return NULL;
    } 

    file = fopen(_path, "r");

    //get map info section
    char mapinfo[MAP_INFOSIZE];
    fgets(mapinfo, MAP_INFOSIZE, file);

    if(!load_map_info(mapinfo, map)){
        printf("Map info invalid!\n");
        free(map);
        return NULL;
    }

    //initialize map and visited map
    map->map = malloc(sizeof(char*)*map->sizey);
    map->visited = malloc(sizeof(bool*)*map->sizey);
    for(int i = 0; i < map->sizex; i++){
        map->map[i] = malloc(sizeof(char)*map->sizex+2);
        map->visited[i] = malloc(sizeof(bool)*map->sizex);
        memset(map->visited[i], false, map->sizex);
    }

    //load the map
    int x = 0;
    while(!feof(file) && x < map->sizey){
        fgets(map->map[x], map->sizex+2, file);
        map->map[x][map->sizex] = '\0';
        x++;
    }

    fclose(file);

    return map;
}

void test_print_map(map_struct* map){
    for(int i = 0; i < map->sizey; i++){
        printf("%s\n", map->map[i]);
    }
    /*
    for(int i = 0; i < map->sizey; i++){
        for(int k = 0; k < map->sizex; k++){
            printf("%d", map->visited[i][k]);
        }
        printf("\n");
    }
    */
}

path* find_start(map_struct* map){
    path* out = malloc(sizeof(path));
    out->history = 0;
    out->size = 0;
    for(int i = 0; i < map->sizey; i++){
        for(int k = 0; k < map->sizex; k++){
            if(map->map[i][k] == map->entry){
                out->y = i;
                out->x = k;
                return out;
            }
        }
    }

    free(out);
    return NULL;
}

bool pos_limits(int a, int limit){
    if(a < 0){
        return false;
    }
    if(a > limit){
        return false;
    }
    return true;
}

bool check_map(int x, int y, map_struct* map){
    if(pos_limits(y, map->sizey-1) && pos_limits(x, map->sizex-1)){
        if(!map->visited[y][x] && map->map[y][x] != map->wall){
            map->visited[y][x] = true;
            return true;
        }
    }
    return false;
}

path* step_path(int x, int y, path* last){
    path* new = malloc(sizeof(path));
    new->x = x;
    new->y = y;
    new->size = last->size + 2;
    new->history = malloc(sizeof(int)*(new->size));
    int i = 0;
    
    for(i = 0; i < last->size; i++){
        new->history[i] = last->history[i];
    }

    new->history[i] = last->x;
    new->history[i+1] = last->y;
    return new;
}

path* shortest_path(queue* q_head){
    queue* working = q_head;
    path* out = q_head->i;
    path* hold;
    while(working!=NULL){
        hold = working->i;
        if(hold->size < out->size){
            out = hold;
        }
        working = working->next;
    }
    path* ret = step_path(out->x, out->y, out);
    working = q_head;
    while(working!=NULL){
        hold = working->i;
        free(hold->history);
        free(hold);
        working = queue_pop(working);
    }

    return ret;
}

path* bfs_pathfind(map_struct* map){
    //add first coordinates to queue
    int cx, cy;
    path* hold;
    path* start_path = find_start(map);
    if(start_path == NULL){
        printf("Map has no start\n");
        return NULL;
    }

    map->visited[start_path->y][start_path->x] = true;
    queue* q_head = NULL;
    q_head = queue_add(start_path, q_head);
    

    while(q_head != NULL){
        
        hold = q_head->i;

        //printf("FROM %d, %d, %c\n", hold->x, hold->y, map->map[hold->y][hold->x]);//test
        
        if(map->map[hold->y][hold->x] == map->exit){
            path* out = shortest_path(q_head);
            return out;
        }

        //top
        cx = hold->x;
        cy = hold->y-1;
        if(check_map(cx, cy, map)){
            //printf("----TO %d, %d, %c\n", cx, cy, map->map[cy][cx]);//test
            queue_add(step_path(cx, cy, hold), q_head);
        }

        //left
        cx = hold->x-1;
        cy = hold->y;
        if(check_map(cx, cy, map)){
            //printf("----TO %d, %d, %c\n", cx, cy, map->map[cy][cx]);//test
            queue_add(step_path(cx, cy, hold), q_head);
        }

        //down
        cx = hold->x;
        cy = hold->y+1;
        if(check_map(cx, cy, map)){
            //printf("----TO %d, %d, %c\n", cx, cy, map->map[cy][cx]);//test
            queue_add(step_path(cx, cy, hold), q_head);
            
        }

        //right
        cx = hold->x+1;
        cy = hold->y;
        if(check_map(cx, cy, map)){
            //printf("----TO %d, %d, %c\n", cx, cy, map->map[cy][cx]);//test
            queue_add(step_path(cx, cy, hold), q_head);
        }
        
        free(hold->history);
        free(hold);
        q_head = queue_pop(q_head);

    }
    printf("Failed to find goal.\n");

    return NULL;
}

void printresult(path* final, map_struct* map){
    int count = 0;
    int cx = final->history[count];
    int cy = final->history[count+1];
    while(count < final->size){
        cx = final->history[count];
        cy = final->history[count+1];
        map->map[cy][cx] = map->path;
        count = count+2;
    }
    test_print_map(map);
    printf("Goal reached in %d steps\n", final->size/2);
}