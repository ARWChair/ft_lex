#include "../incs/ft_lex.h"

static void clear_map_parts(map* current_map, map *new_map, int fail_pos) {
    clear_map(current_map);
    for (int pos = 0; pos < fail_pos; pos++) {
        free(new_map->content[pos].pattern);
        free(new_map->content[pos].action);
        new_map->content[pos].pattern = NULL;
        new_map->content[pos].action = NULL;
    }
    free(new_map->content);
    new_map->content = NULL;
    free(new_map);
    new_map = NULL;
}

map *create_map(ssize_t size) {
    map *create_map = (map*)malloc(sizeof(map));
    if (!create_map)
        return NULL;
    map_content *new_content = (map_content*)malloc(sizeof(map_content) * size);
    if (!new_content) {
        free(create_map);
        return NULL;
    }
    create_map->content = new_content;
    create_map->map_size = size;
    return create_map;
}

map *init_map() {
    return create_map(0);
}

map *append_map(map *old_map, char *pattern, char *action) {
    map *new_map = create_map(old_map->map_size + 1);
    if (!new_map) {
        clear_map(old_map);
        return NULL;
    }
    int map_pos = 0;
    for (; map_pos < old_map->map_size; map_pos++) {
        new_map->content[map_pos].pattern = NULL;
        new_map->content[map_pos].action = NULL;
        new_map->content[map_pos].pattern = ft_strdup(old_map->content[map_pos].pattern);
        new_map->content[map_pos].action = ft_strdup(old_map->content[map_pos].action);
        if (new_map->content[map_pos].pattern == NULL || new_map->content[map_pos].action == NULL) {
            clear_map_parts(old_map, new_map, map_pos);
            return NULL;
        }
    }
    new_map->content[map_pos].pattern = ft_strdup(pattern);
    new_map->content[map_pos].action = ft_strdup(action);
    clear_map(old_map);
    return new_map;
}


map *append_map_and_free(map *old_map, char *pattern, char *action) {
    map *new_map = append_map(old_map, pattern, action);
    if (!new_map)
        return NULL;
    free(pattern);
    free(action);
    return new_map;
}

int get_pos_in_map(map *old_map, char *pattern) {
    if (!pattern)
        return -1;
    if (old_map->map_size == 0)
        return 0;
    int pattern_pos;
    for (int map_pos = 0; map_pos < old_map->map_size; map_pos++) {
        pattern_pos = 0;
        for (; old_map->content[map_pos].pattern[pattern_pos]; pattern_pos++) {
            if (old_map->content[map_pos].pattern[pattern_pos] != pattern[pattern_pos])
                break;
        }
        if (old_map->content[map_pos].pattern[pattern_pos] == 0)
            return map_pos;
    }
    return -2;
}

int remove_map(map *old_map, char *pattern) {
    if (!pattern)
        return -1;
    int pos = get_pos_in_map(old_map, pattern);
    if (pos == -1 || pos == -2)
        return -2;
    if (pos == 0)
        return 0;
    map* new_map = create_map(old_map->map_size - 1);
    if (!new_map)
        clear_map(old_map);
    int skip = 0;
    for (int map_pos = 0; map_pos < old_map->map_size; map_pos++) {
        if (map_pos == pos) {
            skip = -1;
            continue;
        }
        new_map->content[map_pos].pattern = NULL;
        new_map->content[map_pos].action = NULL;
        new_map->content[map_pos].pattern = ft_strdup(old_map->content[map_pos].pattern);
        new_map->content[map_pos].action = ft_strdup(old_map->content[map_pos].action);
        if (new_map->content[map_pos].pattern == NULL || new_map->content[map_pos].action == NULL) {
            clear_map_parts(old_map, new_map, map_pos);
            return -3;
        }
    }
    return 0;
}

void clear_map(map *old_map) {
    if (!old_map)
        return;
    if (!old_map->content)
        return;
    if (old_map->map_size == 0) {
        free(old_map->content);
        old_map->content = NULL;
        free(old_map);
        old_map = NULL;
        return;
    }
    for (int map_pos = 0; map_pos < old_map->map_size; map_pos++) {
        free(old_map->content[map_pos].pattern);
        free(old_map->content[map_pos].action);
        old_map->content[map_pos].pattern = NULL;
        old_map->content[map_pos].action = NULL;
    }
    free(old_map->content);
    old_map->content = NULL;
    free(old_map);
    old_map = NULL;
}

void print_map(map *old_map) {
    if (!old_map)
        return;
    for (int map_pos = 0; map_pos < old_map->map_size; map_pos++) {
        printf("Pattern: %s\nAction: %s\n\n", old_map->content[map_pos].pattern, old_map->content[map_pos].action);
    }
}
