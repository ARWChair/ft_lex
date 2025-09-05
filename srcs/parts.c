#include "../incs/ft_lex.h"

// Using pointer arg, so that C doesn't create a unnecessary copy
// Resets the struct and frees dynamic memory in case of allocation failure
// static void fail_alloc(modified_lexer_file *failed) {
//     failed->star_pos = -1;
//     if (failed->modified_file != NULL)
//         free(failed->modified_file);
//     failed->modified_file = NULL;
//     failed->end_pos = -1;
// }

// Clears the whole lexer. Use outside for clearing at end
void clear_lexer_parts(lexer_string_parts *failed) {
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

// Gets endpos of header and creates text section.
// need to do create checks, if occurent is a valid splitpoint
// modified_lexer_file get_lexer_part(char *file) {
//     modified_lexer_file return_struct;

//     int occurrence = find_first_occurrence_spaces(file, "%%", '\n');
//     is_new_part(file, occurrence);
//     if (occurrence == -1)
//         occurrence = 0;
//     return_struct.modified_file = ft_strdup_end(file, occurrence);
//     if (!return_struct.modified_file)
//         return fail_alloc(&return_struct), return_struct;
//     return_struct.star_pos = 0;
//     return_struct.end_pos = occurrence + ft_strlen("%%\n");
//     return return_struct;
// }

// lexer_parts split_in_parts(char *file) {
//     lexer_parts parts;
//     char *head_modified;
//     char *body_modified;

//     parts.header = get_lexer_part(file);
//     if (!parts.header.modified_file) {
//         free(file);
//         clear_lexer_parts(&parts);
//         return parts;
//     }
//     head_modified = ft_strdup_section(file, parts.header.end_pos, ft_strlen(file));
//     free(file);
//     file = NULL;
//     if (!head_modified)
//         return clear_lexer_parts(&parts), parts;

//     parts.body = get_lexer_part(head_modified);
//     if (!parts.body.modified_file) {
//         free(head_modified);
//         clear_lexer_parts(&parts);
//         return parts;
//     }
//     body_modified = ft_strdup_section(head_modified, parts.body.end_pos, ft_strlen(head_modified));
//     free(head_modified);
//     if (!body_modified)
//         return clear_lexer_parts(&parts), parts;

//     parts.footer = get_lexer_part(body_modified);
//     free(body_modified);
//     if (!parts.footer.modified_file)
//         return clear_lexer_parts(&parts), parts;
//     return parts;
// }

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
    
    lex->lex_parts = temp_part;
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
    
}
