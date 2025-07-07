#include "../incs/ft_lex.h"

static void fail_alloc(lexer_strings_content *failed) {
    failed->start = -1;
    failed->end = -1;
    if (failed->content)
        free(failed->content);
    failed->content = NULL;
}

static void lexar_err_free(ft_lex *lex, lexer_strings_content *strings, int ammount) {
    for (int pos = 0; pos < ammount; pos++)
        free(strings[pos].content);
    shutdown(lex, 1);
}

void clear_lexer_strings(lexer_strings *failed) {
    if (failed->strings) {
        for (int pos = 0; pos < failed->ammount; pos++) {
            fail_alloc(&(failed->strings[pos]));
        }
        free(failed->strings);
    }
    failed->strings = NULL;
    failed->ammount = -1;
}

static lexer_strings_content *append_lexer(ft_lex *lex, lexer_strings lexer_strings, char *new_str, int start, int end) {
    lexer_strings_content *strings;

    strings = (lexer_strings_content *)malloc(sizeof(lexer_strings_content) * (lexer_strings.ammount + 1));
    if (!strings) {
        write(2, "Error: malloc failed in lexer_string_content\n", 45);
        free(new_str);
        shutdown(lex, 1);
    }
    for (int pos = 0; pos < lexer_strings.ammount; pos++) {
        strings[pos].content = ft_strdup(lexer_strings.strings[pos].content); // Segfault
        if (!strings[pos].content)
            lexar_err_free(lex, strings, pos);
        strings[pos].start = lexer_strings.strings[pos].start; // Segfault
        strings[pos].end = lexer_strings.strings[pos].end; // Segfault
        free(lexer_strings.strings[pos].content);
    }
    strings[lexer_strings.ammount].start = start;
    strings[lexer_strings.ammount].end = end;
    strings[lexer_strings.ammount].content = ft_strdup(new_str);
    if (!strings[lexer_strings.ammount].content)
        lexar_err_free(lex, strings, lexer_strings.ammount);
    free(lexer_strings.strings);
    return strings;
}

lexer_strings create_lexer_strings(ft_lex *lex) {
    lexer_strings_content *content;
    lexer_strings strings;
    lexer_strings temp_strings;

    strings.ammount = 0;
    strings.strings = NULL;
    if (!lex->file_content || !lex->file_content[0])
        return strings;
    for (int pos = 0; lex->file_content[pos]; pos++) {
        if (lex->file_content[pos] != '"') //check here, if the quote starts next to escape character
            continue;
        if (lex->file_content[pos] == '"' && lex->file_content[pos - 1] == '\\')
            continue;
        int start = pos;
        char *string_return = get_string(lex, &pos);
        if (!string_return) {
            shutdown(lex, 1);
        }
        content = append_lexer(lex, strings, string_return, start, pos);
        free(string_return);
        strings.ammount++;
        if (!content)
            shutdown(lex, 1);
        strings.strings = content;
    }
    return strings;
}

char *get_string(ft_lex *lex, int *start_pointer) {
    int start = *start_pointer + 1;
    int fallback = start;
    int escape_characters = 0;
    bool found = false;

    for (; lex->file_content[start]; start++) {
        if (lex->file_content[start] == '\n') {
            write(2, "Error: One or more strings are invalid. Newlines or linebreaks are not allowed in a string\n", 91);
            return NULL;
        }
        if (lex->file_content[start] == '"') {
            if (lex->file_content[start - 1] != '\\') {
                found = true;
                break;
            }
            int reverse_start = start - 1;
            for (; reverse_start > 0; reverse_start--) {
                if (lex->file_content[reverse_start] != '\\') {
                    found = true;
                    break;
                }
                escape_characters++;
            }
            if (escape_characters % 2 == 0) {
                found = true;
                start -= escape_characters;
                break;
            }
            escape_characters = 0;
        }
    }
    if (found == false) {
        write(2, "Error: String has no closing quote\n", 35);
        return NULL;
    }
    *start_pointer = start + escape_characters + 1;
    char *str = ft_strdup_section(lex->file_content, fallback, start + escape_characters);
    if (!str)
        write(2, "Error: Malloc failed\n", 21);
    return str;
}
