#ifndef FT_LEX
# define FT_LEX
# define LOOP_BREAKER 2147483647
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct modified_lexer_file {
    char *modified_file;
    int star_pos;
    int end_pos;
}       modified_lexer_file;

typedef struct lexer_parts {
    modified_lexer_file header;
    modified_lexer_file body;
    modified_lexer_file footer;
}               lexer_parts;


// ---------- parts.c ---------- \\'
modified_lexer_file get_lexer_part(char *file);
lexer_parts         split_in_parts(char *file);
void clear_lexer(lexer_parts *failed);

// ---------- utils.c ---------- \\'
int ft_strlen(char *str);
char *ft_strdup_end(char *str, int end);
char *ft_strdup_section(char *str, int start, int end);
char *read_file(int fd);
int is_new_part(char *file, int occurrence);
int find_first_occurrence(char *file, char *str);
int find_first_occurrence_spaces(char *file, char *str, char last_char);
char *replace_string_with_character(char *file, char *replace_string, int start, char characters);

#endif