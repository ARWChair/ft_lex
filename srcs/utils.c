#include "../incs/ft_lex.h"

int ft_strlen(char *str) {
    int pos;

    if (!str)
        return 0;
    for (pos = 0; str[pos]; pos++);
    return pos;
}

char *ft_strdup(char *str) {
    int max_size = (int)ft_strlen(str);
    char *new_str;
    int start;
    
    if (!str)
        return NULL;
    new_str = (char *)malloc(sizeof(char) * (max_size + 1));
    if (!new_str)
        return NULL;
    for (start = 0; str[start]; start++)
        new_str[start] = str[start];
    new_str[start] = 0;
    return new_str;
}

char *ft_strdup_end(char *str, int end) {
    int max_size = (int)ft_strlen(str);
    char *new_str;
    int start;
    
    if (!str)
        return NULL;
    if (max_size <= end)
        new_str = (char *)malloc(sizeof(char) * (max_size + 1));
    else
        new_str = (char *)malloc(sizeof(char) * (end + 1));
    if (!new_str)
        return NULL;
    for (start = 0; str[start] && start < end; start++)
        new_str[start] = str[start];
    new_str[start] = 0;
    return new_str;
}

char *ft_strdup_section(char *str, int start, int end) {
    int max_size = (int)ft_strlen(str);
    char *new_str;
    int index;
    
    if (!str)
        return NULL;
    if (max_size <= end)
        new_str = (char *)malloc(sizeof(char) * (max_size + 1));
    else
        new_str = (char *)malloc(sizeof(char) * (end - start + 1));
    if (!new_str)
        return NULL;
    for (index = start; str[index] && index < end; index++)
        new_str[index - start] = str[index];
    new_str[index - start] = 0;
    return new_str;
}

int find_first_occurrence(char *file, char *str) {
    int index = 0;
    int str_pos = 0;
    int str_len = ft_strlen(str);

    for (int file_pos = 0; file[file_pos]; file_pos++) {
        for (str_pos = 0; str[str_pos]; str_pos++) {
            if (file[str_pos + file_pos] != str[str_pos])
                break;
        }
        if (str_pos == str_len)
            return index;
        if (str_pos == 0)
            index += 1;
        else
            index += str_pos;
    }
    return -1;
}

int find_first_occurrence_spaces(char *file, char *str, char last_char) {
    int index = 0;
    int str_pos = 0;
    int str_len = ft_strlen(str);

    int fallback;
    for (int file_pos = 0; file[file_pos]; file_pos++) {
        for (str_pos = 0; str[str_pos]; str_pos++) {
            if (file[str_pos + file_pos] != str[str_pos])
                break;
        }
        if (str_pos == str_len) {
            fallback = file_pos + str_pos;
            for (; file[fallback]; fallback++) {
                if (file[fallback] == last_char)
                    return index;
                if (file[fallback] != 32)
                    break;
            }
        }
        if (str_pos == 0)
            index += 1;
        else
            index += str_pos;
    }
    return -1;
}

int find_first_occurrence_spaces_end(char *file, char *str, char last_char) {
    int index = 0;
    int str_pos = 0;
    int str_len = ft_strlen(str);

    for (int file_pos = 0; file[file_pos]; file_pos++) {
        for (str_pos = 0; str[str_pos]; str_pos++) {
            if (file[str_pos + file_pos] != str[str_pos])
                break;
        }
        int fallback;
        if (str_pos == str_len) {
            fallback = file_pos + str_pos;
            for (; file[fallback]; fallback++) {
                if (file[fallback] == last_char)
                    return index;
                if (file[fallback] != 32)
                    break;
            }
            if (file[fallback] == 0)
                return index;
        }
        if (str_pos == 0)
            index += 1;
        else
            index += str_pos;
    }
    return -1;
}

char *append_char(char *str, char new) {
    char *return_string;
    int pos;

    if (!str)
        return NULL;
    return_string = (char *)malloc(ft_strlen(str) + 2);
    if (!return_string)
        return NULL;
    for (pos = 0; str[pos]; pos++)
        return_string[pos] = str[pos];
    return_string[pos++] = new;
    return_string[pos] = 0;
    if (str != NULL)
        free(str);
    return return_string;
}

char *read_file(int fd) {
    char *file_content = (char *)malloc(2);
    char read_char;

    if (!file_content)
        return NULL;
    read(fd, &read_char, 1);
    file_content[0] = read_char;
    file_content[1] = 0;
    while (read(fd, &read_char, 1) > 0) {
        file_content = append_char(file_content, read_char);
    }
    return file_content;
}

char *replace_string_with_character(char *file, char *replace_string, int start, char characters) {
    int replace_ammount = ft_strlen(replace_string);

    for (int counter = 0; file[start + counter] && counter < replace_ammount; counter++)
        file[start + counter] = characters;
    return file;
}

int find_char(char *file, char to_find, int start, int end) {
    while (file[start]) {
        if (end != -1 && start == end)
            break;
        if (file[start] == to_find)
            break;
        start++;
    }
    return start;
}

bool is_closing_quote(char *str, int start, char quote) {
    if (!str || !str[start])
        return false;
    if (str[start - 1] != quote && str[start] == quote && str[start + 1])
        start++;
    for (; str[start]; start++) {
        if (str[start] == quote)
            return true;
        if (str[start] == '\\')
            break;
        
    }
    return false;
}

// search to right side till finding a '")' or '" ,'. Jump over '"\'. Do same for right side
int is_new_part(char *file, int occurrence) {
    int start = occurrence;
    int right_dquote = find_char(file, '"', start, -1);
    bool check_closing = is_closing_quote(file, start, '"');
    int right_clambs = find_char(file, ')', start, -1);
    if (right_dquote != right_clambs - 1)
        return start;
    return -1;
    // return occurrence;
}

void terminate_strings(char *file) {
    for (int pos = 0; file[pos]; pos++) {
        if (file[pos] != '"')
            continue;
        if (is_closing_quote(file, pos - 1, '"') == false)
            continue;
        int ending = find_char(file, '"', pos + 1, ft_strlen(file));
        int start = pos + 1;
        for (; file[start] && start < ending; start++) {
            file[start] = 'X';
        }
        pos = start;
    }
}

int skip_spaces_parts(char *file, int start) {
    int start_pos = start;

    for(; file[start_pos]; start_pos++) {
        if (file[start_pos + 1] != 0 && file[start_pos + 1] == '\n')
            continue;
        start_pos = start_pos + 2;
        break;
    }
    return start_pos;
}

int get_and_eliminate_part_spliter(char *file) {
    int check_spliter = find_first_occurrence_spaces_end(file, "%%", '\n');
    if (check_spliter == -1)
        return -1;
    if (check_spliter > 0 && file[check_spliter - 1] != '\n')
        return -1;
    file[check_spliter] = 'X';
    file[check_spliter + 1] = 'X';
    return check_spliter;
}

char *get_line(char *str, int *start) {
    int start_pos = *start;
    int end = start_pos;
    bool inside = false;

    int check;
    for (;str[end]; end++) {
        if (str[end] == '{')
            inside = true;
        if (str[end] == '}' && inside == true)
            inside = false;
        if (str[end] == '\n' && inside == false)
            break;
    }
    if (!str[end] && inside == true) {
        *start = -1;
        return NULL;
    }
    char *return_str = ft_strdup_section(str, start_pos, end);
    if (!return_str)
        return NULL;
    *start = end;
    return return_str;
}

char    *get_makro(char *header, int *start) {
    int start_pos = *start;
    int end = start_pos;
    bool format_correct = false;

    if (!(header[end] >= 'a' && header[end] <= 'z' || header[end] >= 'A' && header[end] <= 'Z')) {
        write(2, "Error: Name of Makro staring with invalid Character. Only valid char or Newline in line allowed\n", 96);
        return NULL;
    }
    end++;
    for (; header[end]; end++) {
        if (header[end] == '\n' && format_correct == false) {
            write(2, "Error: No value found for Makro\n", 32);
            *start = end;
            return NULL;
        }
        if (header[end] == 32 || header[end] == 9) {
            end = skip_spaces(header, end);
            if (skip_spaces(header, end) == 10) {
                write(2, "Error: No value found for Makro\n", 32);
                *start = end;
                return NULL;
            }
        }
    }
    if (header[end] == 0 && format_correct == false) {
        write(2, "Error: No value found for Makro\n", 32);
        *start = end;
        return NULL;
    }
    *start = end;
    return NULL;
}

int     skip_spaces(char *header, int pos) {
    for (; header[pos]; pos++) {
        if (header[pos] != 32 && header[pos] != 9)
            break;
    }
    return pos;
}

map *split_line_into_map(map *mp, char *line) {
    char *pattern = NULL;
    char *action = NULL;
    bool regex = false;
    int start = 0;
    int pos = 0;

    for (; line[pos] && (line[pos] == 32 || line[pos] == 9); pos++);
    start = pos;

    if (line[pos] == '"') {
        int ending = find_char(line, '"', pos + 1, ft_strlen(line));
        pos += ending + 1;
    } else if (line[pos] == '[') {
        int ending = find_char(line, ']', pos + 1, ft_strlen(line));
        pos += ending + 1;
    } else {
        int ending = find_char(line, 32, pos + 1, ft_strlen(line));
        pos += ending;
    }

    if (!line[pos]) {
        action = ft_strdup("{ ECHO; }");
        if (!action)
            goto cleanup;
    }

    pattern = ft_strdup_section(line, start, pos);
    if (!pattern)
        goto cleanup;
    for (; line[pos] && (line[pos] == 32 || line[pos] == 9); pos++);
    if (!action) {
        action = ft_strdup_section(line, pos, ft_strlen(line));
        if (!action)
            goto cleanup;
    }

    map *new_map = append_map_and_free(mp, pattern, action);
    if (!new_map)
        goto cleanup;
    return new_map;

    cleanup:
        free(pattern);
        free(action);
        clear_map(mp);
        return NULL;
}

char    *isolate_string(char *header, int *pos) {
    int temp = *pos;
    bool closing = false;

    for (; header[temp]; temp++) {
        if (header[temp] == '%' && header[temp + 1] && header[temp + 1] == '}') {
            closing = true;
            break;
        }
    }
    if (!header[temp] && closing == false) {
        write(2, "Error: No closing characters found for definition\n", 50);
        return NULL;
    }
    if (header[temp + 2] && header[temp + 2] != '\n') {
        write(2, "Error: No character allowed after closing definition\n", 53);
        return NULL;
    }
    if (header[temp - 1] && header[temp - 1] != '\n') {
        write(2, "Error: No character allowed after closing definition\n", 53);
        return NULL;
    }
    char *returning = ft_strdup_section(header, *pos, temp - 1);
    if (!returning)
        return NULL;
    *pos = temp + 2;
    return returning;
}

char **append_string(char **base, char *new_string) {
    if (base == NULL) {
        char **return_string = (char **)malloc((sizeof(char *) * 2));
        if (!return_string)
            return NULL;
        return_string[0] = ft_strdup(new_string);
        if (!return_string[0]) {
            free(return_string);
            return_string = NULL;
            return false;
        }
        return_string[1] = 0;
        return return_string;
    }
    
    int len = 0;
    for (; base[len]; len++);

    char **return_string = (char **)malloc(sizeof(char *) * (len + 2));
    if (!return_string)
        return NULL;
    int pos = 0;
    printf("len: %i\n", len);
    for (; pos < len; pos++) {
        return_string[pos] = base[pos];
    }
    printf("%i\n", len);
    return_string[pos++] = ft_strdup(new_string);
    return_string[pos] = 0;
    free(base);
    return return_string;
}

void    shutdown(ft_lex *lex, bool error) {
    if (lex->parts != NULL)
        clear_lexer_parts(lex->parts);
    if (lex->lex_string_parts != NULL)
        clear_lexer_string_parts(lex->lex_string_parts);
    lex->lex_string_parts = NULL;
    if (lex->lex_strings != NULL)
        clear_lexer_strings(lex->lex_strings);
    lex->lex_strings = NULL;
    int check_fd = fcntl(lex->file_fd, F_GETFD);
    if (!(check_fd == -1 && errno == EBADF))
        close(lex->file_fd);
    if (lex->file_content)
        free(lex->file_content);
    lex->file_content = NULL;
    if (error == true)
        exit(1);
}
