#include <stdio.h>

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

int main() {
    printf("%i\n", find_first_occurence("aabbccdgdeef", "b"));
}
