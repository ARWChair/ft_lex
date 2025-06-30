// Check for parts
// first is optional
// parts are seperated with %%

#include "../incs/ft_lex.h"

int *part_count(char *file) {
    static int parts_from_till[6];
    int part_pos = 0;

    parts_from_till[part_pos++] = 0;
    // find occurence
    // save in integer the return
    // replace those 3 charecters with XXX
    // search to right side till finding a '")' or '" ,'. Jump over '"\'. Do same for right side
    
    for (int loop; loop < LOOP_BREAKER; loop++) {
        int occurence = find_first_occurence(file, "%%\n");
        if (occurence == -1)
            break;
        int end = is_new_part(file, occurence);
        if (end != -1) {
            if (part_pos > 6)
                break;
            if (part_pos == 5) {
                parts_from_till[5] = ft_strlen(file);
                break;
            }
            parts_from_till[part_pos++] = end;
            parts_from_till[part_pos++] = end + 1;
        }
        file = replace_string_with_character(file, "%%\n", occurence, 'X');
    }
    // occurence = find_first_occurence(file, "%%\n");
    // file = replace_string_with_character(file, "%%\n", occurence, 'X');
    printf("%s\n", file);
    // printf("%i\n", occurence);

    return parts_from_till;
}

// char    **split_in_parts(char *file) {

// }

// write (1, "%%\n", 3);
// printf ("\n%%\n");