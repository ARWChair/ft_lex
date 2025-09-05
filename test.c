#include "./incs/ft_lex.h"

int main() {
    ft_lex  lex;

    lex.file_fd = open("./files/ex1.l", O_RDWR);
    if (lex.file_fd < 3)
        return -1;
    lex.file_content = read_file(lex.file_fd);
    lex.lex_parts = NULL;
    lex.lex_strings = NULL;
    split_in_parts(&lex);
    shutdown(&lex, false);
    return (0);
}
