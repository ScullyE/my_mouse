#ifndef PATH_LIB_H
#define PATH_LIB_H

    #define MAP_INFOSIZE 16

    typedef struct path_s {
        int x, y, size;
        int* history;
    } path;

    typedef struct map_s {
        int sizex, sizey;
        char wall, empty, path, entry, exit;
        char** map;
        bool** visited;
    } map_struct;

    map_struct* load_map(char* _path);
    void test_print_map(map_struct* map);
    path* bfs_pathfind(map_struct* map);
    void printresult(path* final, map_struct* map);

#endif