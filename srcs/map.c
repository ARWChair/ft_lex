#include "../incs/ft_lex.h"

map *create_map() {
    map *create_map = (map*)malloc(sizeof(map));
    if (!create_map)
        return NULL;
    create_map->map_size = 0;
    return create_map;
}

int append_map(map *map, char *pattern, char *action) {
    
}

int get_pos_in_map(map *map, char *pattern) {

}

int remove_map(map *map, char *pattern) {

}

int clear_map(map *map) {

}
