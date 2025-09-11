#include "../incs/ft_lex.h"

// ------------------- lexer_parts ------------------- \\'

void clear_lexer_parts(lexer_parts *lex) {
    if (!lex)
        return;
    if (!lex->middle) {
        free(lex);
        lex = NULL;
        return;
    }
    if (!lex->middle->pairs) {
        free(lex->middle);
        lex->middle = NULL;
        free(lex);
        lex = NULL;
        return;
    }
    clear_map(lex->middle->pairs);
    lex->middle->pairs = NULL;
    free(lex->middle);
    lex->middle = NULL;
    free(lex);
    lex = NULL;
}

bool format_header_part(ft_lex *lex) {
    map *mp = NULL;
    char **definition = NULL;
    char *single_definition = NULL;
    char *header = NULL;
    char **line = NULL;
    
    mp = init_map();
    header = lex->lex_string_parts->header;
    for (int pos = 0; header[pos]; pos++) {
        if (header[pos] == '%' && header[pos + 1] != '{') {
            header_invalid_definition_opener();
            goto cleanup;
        } else if (header[pos] == '%' && header[pos + 1] == '{') {
            if (header[pos - 1] && header[pos - 1] != '\n') {
                header_definition_not_on_newline()
                goto cleanup;
            }
            pos += 2;
            if (header[pos] && header[pos] != '\n') {
                header_newline_after_definition_opener();
                goto cleanup;
            }
            pos++;
            single_definition = isolate_string(header, &pos);
            if (!single_definition)
                goto cleanup;
            definition = append_string(definition, single_definition);
            free(single_definition);
            single_definition = NULL;
            if (header[pos] != 0)
                pos++;
        }
        if (header[pos] == '\n')
            continue;

        line = get_makro(header, &pos);
        if (!line)
            goto cleanup;
        mp = append_map(mp, line[0], line[1]);
        if (!mp)
            goto cleanup;
    }
    // for (int i = 0; definition[i]; i++) {
    //     printf("%s\n", definition[i]);
    // }
    return true;
    cleanup:
        if (mp)
            clear_map(mp);
        if (definition != NULL) {
            for (int i = 0; definition[i]; i++) {
                free(definition[i]);
                definition[i] = NULL;
            }
            free(definition);
            definition = NULL;
        }
        free(single_definition);
        if (line) {
            free(line[0]);
            line[0] = NULL;
            free(line[1]);
            line[1] = NULL;
            free(line);
            line = NULL;
        }
        single_definition = NULL;
        mp = NULL;
        return false;
}

bool format_body_part(ft_lex *lex) {
    map *mp = init_map();
    if (!mp)
        shutdown(lex, true);

    char *line = NULL;
    int pos = 0;

    for (; lex->lex_string_parts->body[pos]; pos++) {
        line = get_line(lex->lex_string_parts->body, &pos);
        if (pos == -1 && !line) {
            parts_multiline_open();
            shutdown(lex, true);
        }
        if (!line)
            shutdown(lex, true);

        mp = split_line_into_map(mp, line);
        if (!mp) {
            free(line);
            shutdown(lex, true);
        }
        free(line);
        line = NULL;
    }
    if (!lex->parts) {
        lex->parts = (lexer_parts *)malloc(sizeof(lexer_parts));
        if (!lex->parts) {
            clear_map(mp);
            return false;
        }
        lex->parts->middle = NULL;
    }
    if (!lex->parts->middle) {
        lex->parts->middle = (lexer_middle_struct *)malloc(sizeof(lexer_middle_struct));
        if (!lex->parts->middle) {
            clear_map(mp);
            free(lex->parts);
            return false;
        }
        lex->parts->middle->pairs = NULL;
    }
    lex->parts->middle->pairs = mp;
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
    if (failed)
        free(failed);
    failed = NULL;
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

    temp_part->body = ft_strdup_section(lex->file_content, skip_spaces_parts(lex->file_content, check_header) + 1, check_body);
    if (!temp_part->body)
        goto cleanup;
    int footer_section = skip_spaces_parts(lex->file_content, check_body);
    int file_size = ft_strlen(lex->file_content);
    if (file_size - footer_section == 0)
        temp_part->footer = ft_strdup("");
    else
        temp_part->footer = ft_strdup_section(lex->file_content, footer_section + 1, file_size);
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
