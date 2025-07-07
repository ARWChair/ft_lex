#include "../incs/ft_lex.h"

// int main() {
//     int fd = open("./files/ex1.l", O_RDWR);
//     if (fd < 3)
//         return -1;
//     char *file = read_file(fd);

//     // printf("%i\n", fd);
//     // printf("%s\n", temp);
//     // int *temp2 = part_count(temp);
//     // printf("\n\n%i, %i, %i, %i, %i, %i\n", temp2[0], temp2[1], temp2[2], temp2[3], temp2[4], temp2[5]);
//     // printf("%s\n", file);
//     lexer_parts parts = split_in_parts(file);
//     // printf("%s, %i\n---\n%s, %i\n---\n%s, %i\n", parts.header.modified_file, ft_strlen(parts.header.modified_file), parts.body.modified_file, ft_strlen(parts.body.modified_file), parts.footer.modified_file, ft_strlen(parts.footer.modified_file));
//     clear_lexer_parts&parts);
//     close(fd);
// }