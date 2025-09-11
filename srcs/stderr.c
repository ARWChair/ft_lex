#include "../incs/ft_lex.h"

void makro_starting_invalid_char() {
    write(2, "Error: Name of Makro staring with invalid Character. Only valid char or Newline in line allowed\n", 96);
}

void makro_invalid_name() {
    write(2, "Error: Name of Makro containing invalid character.\n", 51);
}

void makro_no_value() {
    write(2, "Error: Value of Makro not found.\n", 33);
}