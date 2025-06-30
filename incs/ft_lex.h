#ifndef FT_LEX
# define FT_LEX
# define LOOP_BREAKER 2147483647
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

// ---------- parts.c ---------- \\'
int *part_count(char *file);

// ---------- utils.c ---------- \\'
int ft_strlen(char *str);
char *read_file(int fd);
int is_new_part(char *file, int occurence);
int find_first_occurence(char *file, char *str);
char *replace_string_with_character(char *file, char *replace_string, int start, char characters);

#endif