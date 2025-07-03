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

    for (int file_pos = 0; file[file_pos]; file_pos++) {
        for (str_pos = 0; str[str_pos]; str_pos++) {
            if (file[str_pos + file_pos] != str[str_pos])
                break;
        }
        if (str_pos == str_len) {
            int fallback = file_pos + str_pos;
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

char *append_char(char *str, char new) {
    char *return_string = (char *)malloc(ft_strlen(str) + 2);
    int pos;

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
