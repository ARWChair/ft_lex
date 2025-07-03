#include "./incs/ft_lex.h"

int main() {
    int fd = open("./files/ex1.l", O_RDWR);
    if (fd < 3)
        return -1;
    char *file = read_file(fd);
    lexer_strings strings = create_lexer_strings(file);
    for (int start = 0; start < strings.ammount; start++) {
        printf("%s\n", strings.strings[start].content);
    }
    clear_lexer_strings(&strings);
    free(file);
    close(fd);
}

// Wenn string nicht geschlossen, dann darf maximal bis newline gehen