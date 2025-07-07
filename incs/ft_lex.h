#ifndef FT_LEX
# define FT_LEX
# define LOOP_BREAKER 2147483647
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct modified_lexer_file {
    char *modified_file;
    int star_pos;
    int end_pos;
}               modified_lexer_file;

typedef struct lexer_parts {
    modified_lexer_file header;
    modified_lexer_file body;
    modified_lexer_file footer;
}               lexer_parts;


typedef struct lexer_strings_content {
    int start;
    int end;
    char *content;
}               lexer_strings_content;

typedef struct lexer_strings {
    int ammount;
    lexer_strings_content *strings;
}               lexer_strings;

typedef struct ft_lex {
    lexer_strings   *lex_strings;
    lexer_parts     *lex_parts;
    char            *file_content;
    int             file_fd;
}               ft_lex;

// ---------- parts.c ---------- \\'
modified_lexer_file get_lexer_part(char *file);
lexer_parts         split_in_parts(char *file);
void clear_lexer_parts(lexer_parts *failed);

// ---------- strings.c -------- \\'
void clear_lexer_strings(lexer_strings *failed);
char *get_string(ft_lex *lex, int *start);
lexer_strings create_lexer_strings(ft_lex *lex);

// ---------- utils.c ---------- \\'
int     ft_strlen(char *str);
char    *ft_strdup(char *str);
char    *ft_strdup_end(char *str, int end);
char    *ft_strdup_section(char *str, int start, int end);
char    *read_file(int fd);
int     is_new_part(char *file, int occurrence);
int     find_first_occurrence(char *file, char *str);
int     find_first_occurrence_spaces(char *file, char *str, char last_char);
char    *replace_string_with_character(char *file, char *replace_string, int start, char characters);
void    shutdown(ft_lex *lex, bool error);

#endif