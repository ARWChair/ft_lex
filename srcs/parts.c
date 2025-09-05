#include "../incs/ft_lex.h"

// ------------------- lexer_parts ------------------- \\'

void clear_lexer_parts(lexer_parts *lex) {
    if (lex->middle) {
        free(lex->middle->action);
        free(lex->middle->pattern);
        lex->middle->action = NULL;
        lex->middle->pattern = NULL;
        lex->middle = NULL;
    }
}

bool format_header_part(ft_lex *lex) {
    return true;
}

bool format_body_part(ft_lex *lex) {
    
    return true;
}

bool format_footer_part(ft_lex *lex) {
    return true;
}

void split_parts(ft_lex *lex) {
    if (format_header_part(lex) == false)
        shutdown(lex, true);
    if (format_body_part(lex) == false)
        shutdown(lex, true);
    if (format_footer_part(lex) == false)
        shutdown(lex, true);
}

// ------------------- lexer_string_parts ------------------- \\'

// Clears the whole lexer. Use outside for clearing at end
void clear_lexer_string_parts(lexer_string_parts *failed) {
    if (failed->header)
        free(failed->header);
    if (failed->body)
        free(failed->body);
    if (failed->footer)
        free(failed->footer);
    failed->header = NULL;
    failed->body = NULL;
    failed->footer = NULL;
}


bool check_for_parts(ft_lex *lex, char *temp) {
    int check_header = get_and_eliminate_part_spliter(temp);
    if (check_header == -1)
        return false;

    int check_body = get_and_eliminate_part_spliter(temp);
    if (check_body == -1)
        return false;

    int check_valid = find_first_occurrence_spaces_end(temp, "%%", '\n');
    if (check_valid != -1)
        return false;

    lexer_string_parts *temp_part = (lexer_string_parts *)malloc(sizeof(lexer_string_parts));
    if (!temp_part)
        goto cleanup;
    temp_part->header = NULL;
    temp_part->body = NULL;
    temp_part->footer = NULL;
    if (check_header == 0)
        temp_part->header = ft_strdup("");
    else
        temp_part->header = ft_strdup_end(lex->file_content, check_header);
    if (!temp_part->header)
        goto cleanup;

    temp_part->body = ft_strdup_section(lex->file_content, skip_spaces_parts(lex->file_content, check_header), check_body);
    if (!temp_part->body)
        goto cleanup;
    
    temp_part->footer = ft_strdup_section(lex->file_content, skip_spaces_parts(lex->file_content, check_body), ft_strlen(lex->file_content));
    if (!temp_part->footer)
        goto cleanup;
    
    lex->lex_string_parts = temp_part;
    return true;

    cleanup:
        free(temp_part->header);
        free(temp_part->body);
        free(temp_part->footer);
        free(temp_part);
        return false;
}

void    split_in_parts(ft_lex *lex) {
    if (!lex->file_content)
        shutdown(lex, true);
    char *temp = ft_strdup(lex->file_content);
    if (!temp)
        shutdown(lex, true);

    terminate_strings(temp);
    if (check_for_parts(lex, temp) == false) {
        free(temp);
        shutdown(lex, true);
    }
    free(temp);
    split_parts(lex);
}
