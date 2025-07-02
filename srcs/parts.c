#include "../incs/ft_lex.h"

// Using pointer arg, so that C doesn't create a unnecessary copy
// Resets the struct and frees dynamic memory in case of allocation failure
static void fail_alloc(modified_lexer_file *failed) {
    failed->star_pos = -1;
    if (failed->modified_file != NULL)
        free(failed->modified_file);
    failed->modified_file = NULL;
    failed->end_pos = -1;
}

// Clears the whole lexer. Use outside for clearing at end
void clear_lexer(lexer_parts *failed) {
    fail_alloc(&(failed->header));
    fail_alloc(&(failed->body));
    fail_alloc(&(failed->footer));
}

// Gets endpos of header and creates text section.
// need to do create checks, if occurent is a valid splitpoint
modified_lexer_file get_lexer_part(char *file) {
    modified_lexer_file return_struct;

    int occurrence = find_first_occurrence_spaces(file, "%%", '\n');
    if (occurrence == -1)
        occurrence = 0;
    return_struct.modified_file = ft_strdup_end(file, occurrence);
    if (!return_struct.modified_file)
        return fail_alloc(&return_struct), return_struct;
    return_struct.star_pos = 0;
    return_struct.end_pos = occurrence + ft_strlen("%%\n");
    return return_struct;
}

lexer_parts split_in_parts(char *file) {
    lexer_parts parts;
    char *head_modified;
    char *body_modified;

    parts.header = get_lexer_part(file);
    if (!parts.header.modified_file) {
        free(file);
        clear_lexer(&parts);
        return parts;
    }
    head_modified = ft_strdup_section(file, parts.header.end_pos, ft_strlen(file));
    free(file);
    file = NULL;
    if (!head_modified)
        return clear_lexer(&parts), parts;

    parts.body = get_lexer_part(head_modified);
    if (!parts.body.modified_file) {
        free(head_modified);
        clear_lexer(&parts);
        return parts;
    }
    body_modified = ft_strdup_section(head_modified, parts.body.end_pos, ft_strlen(head_modified));
    free(head_modified);
    if (!body_modified)
        return clear_lexer(&parts), parts;

    parts.footer = get_lexer_part(body_modified);
    free(body_modified);
    if (!parts.footer.modified_file)
        return clear_lexer(&parts), parts;
    return parts;
}
