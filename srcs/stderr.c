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

void header_invalid_definition_opener() {
    write(2, "Error: Wrong formating in Header-part. No matching character found after % sign.\n", 81);
}

void header_definition_not_on_newline() {
    write(2, "Error: Opening definition must be after Newline.\n", 49);
}

void header_newline_after_definition_opener() {
    write(2, "Error: Newline must be after definition opener.\n", 48);
}

void parts_multiline_open() {
    write(2, "Error: Multiline action not closed.\n", 36);
}

void utils_no_closing_definition() {
    write(2, "Error: No closing characters found for definition.\n", 51);
}

void utils_no_character_allowed_after_closing() {
    write(2, "Error: No character allowed after closing definition.\n", 54);
}

void utils_no_character_allowed_before_closing() {
    write(2, "Error: No character allowed before closing definition.\n", 55);
}

void utils_invalid_char_after_action() {
    write(2, "Error: Invalid character found after action.\n", 45);
}

void parts_same_pattern_twice() {
    write(2, "Error: The same regex-makro can't be in the list twice.\n", 56);
}