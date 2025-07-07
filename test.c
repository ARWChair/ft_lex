#include "./incs/ft_lex.h"

int main() {
    ft_lex  lex;

    lex.file_fd = open("./files/ex1.l", O_RDWR);
    if (lex.file_fd < 3)
        return -1;
    lex.file_content = read_file(lex.file_fd);
    lex.lex_parts = NULL;
    lex.lex_strings = NULL;
    lexer_strings temp = create_lexer_strings(&lex);
    lex.lex_strings = &temp;
    for (int pos = 0; pos < lex.lex_strings->ammount; pos++) {
        printf("%s\n", lex.lex_strings->strings[pos].content);
    }
    shutdown(&lex, false);
    return (0);
}

// In strings is an error. Prints errors to often
// Wenn string nicht geschlossen, dann darf maximal bis newline gehen