#ifndef FT_LEX
# define FT_LEX
# define LOOP_BREAKER 2147483647
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct lexer_string_parts {
    char                    *header;
    char                    *body;
    char                    *footer;
}               lexer_string_parts;

typedef struct map_content {
    char                    *pattern;
    char                    *action;
}               map_content;

typedef struct map {
    map_content             *content;
    ssize_t                 map_size;
}               map;

typedef struct lexer_top_struct {
    char                    **definitions;
    map                     *pairs;
}               lexer_top_struct;

typedef struct lexer_middle_struct {
    map                     *pairs;
}               lexer_middle_struct;

typedef struct lexer_parts {
    lexer_top_struct        *top;
    lexer_middle_struct     *middle;
}               lexer_parts;

typedef struct lexer_strings_content {
    int                     start;
    int                     end;
    char                    *content;
}               lexer_strings_content;

typedef struct lexer_strings {
    int                     ammount;
    lexer_strings_content   *strings;
}               lexer_strings;

typedef struct ft_lex {
    lexer_strings           *lex_strings;
    lexer_string_parts      *lex_string_parts;
    lexer_parts             *parts;
    char                    *file_content;
    int                     file_fd;
}               ft_lex;

// ---------- map.c ---------- \\'
map     *init_map();
map     *create_map(ssize_t size);
map     *append_map(map *map, char *pattern, char *action);
map     *append_map_and_free(map *map, char *pattern, char *action);
int     get_pos_in_map(map *map, char *pattern);
int     remove_map(map *map, char *pattern);
void    clear_map(map *map);
void    print_map(map *old_map);

// ---------- parts.c ---------- \\'
void    clear_lexer_string_parts(lexer_string_parts *failed);
void    clear_lexer_parts(lexer_parts *lex);
void    split_in_parts(ft_lex *lex);
bool    check_for_parts(ft_lex *lex, char *temp);
bool    format_header_part(ft_lex *lex);
bool    format_body_part(ft_lex *lex);
bool    format_footer_part(ft_lex *lex);
void    split_parts(ft_lex *lex);

// ---------- strings.c -------- \\'
void            clear_lexer_strings(lexer_strings *failed);
char            *get_string(ft_lex *lex, int *start);
lexer_strings   create_lexer_strings(ft_lex *lex);

// ---------- utils.c ---------- \\'
int     ft_strlen(char *str);
char    *ft_strdup(char *str);
char    *ft_strdup_end(char *str, int end);
char    *ft_strdup_section(char *str, int start, int end);
char    *read_file(int fd);
int     is_new_part(char *file, int occurrence);
int     find_first_occurrence(char *file, char *str);
int     find_first_occurrence_spaces(char *file, char *str, char last_char);
int     find_first_occurrence_spaces_end(char *file, char *str, char last_char);
char    *replace_string_with_character(char *file, char *replace_string, int start, char characters);
void    terminate_strings(char *file);
int     skip_spaces_parts(char *file, int start);
int     get_and_eliminate_part_spliter(char *file);
char    *get_line(char *str, int *start);
map     *split_line_into_map(map* mp, char *line);
char    *isolate_string(char *header, int *pos);
char    **append_string(char **base, char *new_string);
void    shutdown(ft_lex *lex, bool error);

#endif