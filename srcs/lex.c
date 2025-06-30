#include "../incs/ft_lex.h"

int main() {
    int fd = open("./files/ex1.l", O_RDWR);
    if (fd < 3)
        return -1;
    char *temp = read_file(fd);

    // printf("%i\n", fd);
    // printf("%s\n", temp);
    part_count(temp);

}