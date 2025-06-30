#include "../incs/ft_lex.h"

int ft_strlen(char *str) {
    int pos;

    for (pos = 0; str[pos]; pos++);
    return pos;
}

int find_first_occurence(char *file, char *str) {
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
    printf("%i\n", replace_ammount);

    for (int counter = 0; file[start + counter] && counter < replace_ammount; counter++)
        file[start + counter] = characters;
    return file;
}

int is_new_part(char *file, int occurence) {

}

//aabbccdeef
//de