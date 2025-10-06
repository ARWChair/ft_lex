#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#define RETURN_STATE(state_actions, retval) do { state_actions; return (retval); } while (0)

// ---------- Helper ---------- \\'

int sstrlen(char *string) {
    if (!string)
        return 0;
    int pos = 0;
    while (string[pos])
        pos++;
    return pos;
}

int dstrlen(char **strings) {
    int pos = 0;

    while (strings[pos])
        pos++;
    return pos;
}

char *ft_strdup(char *to_dup) {
    char *ret = NULL;

    ret = (char *)malloc(sizeof(char) * (sstrlen(to_dup) + 1));
    if (!ret)
        return NULL;
    
    int pos = 0;
    for (; to_dup[pos]; pos++) {
        ret[pos] = to_dup[pos];
    }
    ret[pos] = 0;
    return ret;
}

char *ft_strdup_section(char *str, int start, int end) {
    int max_size = (int)sstrlen(str);
    char *new_str;
    int index;
    
    if (!str)
        return NULL;
    if (max_size <= end)
        new_str = (char *)malloc(sizeof(char) * (max_size + 1));
    else
        new_str = (char *)malloc(sizeof(char) * (end - start + 1));
    if (!new_str)
        return NULL;
    for (index = start; str[index] && index < end; index++)
        new_str[index - start] = str[index];
    new_str[index - start] = 0;
    return new_str;
}

char *ft_strdup_not_section(char *str, int start, int end) {
    int max_size = (int)sstrlen(str);
    char *new_str;
    
    if (!str)
        return NULL;
    new_str = (char *)malloc(sizeof(char) * (max_size - (end - start) + 1));
    if (!new_str)
        return NULL;
    int index = 0;
    int diff = 0;
    for (; str[index]; index++) {
        if (index == start) {
            diff = end - start;
            index = end;
        }
        new_str[index - diff] = str[index]; 
    }
    new_str[index - diff] = 0;
    return new_str;
}

void dfree(char **base) {
    if (base == NULL)
        return;
    for (int pos = 0; base[pos]; pos++) {
        free(base[pos]);
        base[pos] = NULL;    
    }
    free(base);
    base = NULL;
}

void free_start(char **base, int max) {
    for (int pos = 0; base[pos] && pos < max; pos++) {
        free(base[pos]);
        base[pos] = NULL;
    }
    free(base);
    base = NULL;
}

// ---------- Normal functions ---------- \\'

char **fill_return_pair(char **return_pair, char *first, char *second) {
    return_pair[0] = first;
    return_pair[1] = second;
    return_pair[2] = 0;
    return return_pair;
}

// Write function that checks if valid
bool precheck(char *argv) {
    int pos = 0;
    int braces = 0;
    for (; argv[pos]; pos++) {
        if (argv[pos] == '[' || argv[pos] == ']')
            return false;
        if (argv[pos] == '(' || argv[pos] == '{'
            || argv[pos] == '}' || argv[pos] == ')')
            braces++;
    }
    if (braces != 2)
        return false;
    return true;
}

bool spacer_loop(char *argv, int *start, int level, char brace, int *reset) {
    int pos = *start;
    char closing;
    bool found = false;
    for (; argv[pos]; pos++) {
        if (argv[pos] == '[' || argv[pos] == '{' || argv[pos] == '(') {
            level++;
            if (brace == 0) {
                *reset = pos;
                brace = argv[pos];
                if (brace != '(')
                    brace++;
            }
        }
        if (argv[pos] == ']' || argv[pos] == '}' || argv[pos] == ')')
            level--;
        if (argv[pos] - 1 == brace && level == 0) {
            pos++;
            found = true;
            break;
        }
    }
    if (!argv[pos] && found == false)
        return false;
    *start = pos;
    return true;
}
    
char **add_to_pair(char **base, char *news) {
    char **new_pairs = NULL;

    if (!base) {
        new_pairs = (char **)malloc(sizeof(char *) * 2);
        if (!new_pairs)
            return NULL;
        new_pairs[0] = strdup(news);
        if (!new_pairs[0]) {
            free(new_pairs);
            new_pairs = NULL;
            return NULL;
        }
        new_pairs[1] = 0;
        return new_pairs;
    }
    new_pairs = (char **)malloc(sizeof(char *) * (dstrlen(base) + 2));
    if (!new_pairs)
        return NULL;
    int pos = 0;
    for (; base[pos]; pos++) {
        new_pairs[pos] = strdup(base[pos]);
        if (!new_pairs[pos]) {
            free_start(new_pairs, pos);
        }
    }
    new_pairs[pos++] = strdup(news);
    if (!new_pairs[pos - 1]) {
        free_start(base, pos - 1);
        return NULL;
    }
    new_pairs[pos] = 0;
    free(base);
    return new_pairs;
}

char **split_in_pairs(char *argv, char **pairs, int *check) {
    if (!argv)
        return NULL;
    int len = sstrlen(argv);
    if (len == 0)
        RETURN_STATE(*check = 0, pairs);
    int pos = 0;
    char brace;
    for (; argv[pos]; pos++) {
        if (argv[pos] != '[' && argv[pos] != '{' && argv[pos] != '(')
            continue;
        brace = argv[pos];
        pos++;
        break;
    }
    if (!argv[pos])
        RETURN_STATE(*check = 1, pairs);
    if (brace != '(')
        brace++;
    int start = pos;
    if (spacer_loop(argv, &pos, 1, brace, &start) == false)
        RETURN_STATE(*check = 2, NULL);

    char **return_pair = (char **)malloc(sizeof(char *) * 3);
    if (!return_pair)
        return NULL;
    char *first = ft_strdup_section(argv, 0, pos);
    if (!first)
        return free(return_pair), NULL;
    char *second = NULL, *temp = NULL;
    if (pos == len) {
        pos = start;
        if (spacer_loop(argv, &pos, 0, 0, &start) == false) {
            *check = 4;
            goto cleanup;
        }
        second = ft_strdup_section(argv, start, pos);
        temp = ft_strdup_not_section(first, start, pos);
        if (!temp)
            goto cleanup;
        free(first);
        first = temp;
        if (precheck(argv) == true)
            return *check = 0, fill_return_pair(return_pair, first, second);
    } else
        second = ft_strdup_section(argv, pos, len);
    if (!second)
        goto cleanup;
    return fill_return_pair(return_pair, first, second);

    cleanup:
        if (first) {
            free(first);
            first = NULL;
        }
        if (second) {
            free(second);
            second = NULL;
        }
        if (temp) {
            free(temp);
            temp = NULL;
        }
        return NULL;
}


/*
    Example:
    {Test}({test}{lol}) -> {Test} ({test} {lol})  -> {Test} {test} {cool}                                               ✅
    (wow){thi[is(wow)(cool)](test)s} -> (wow) {this} [is(wow)(cool)] (test) -> (wow) {this} [is] (wow) (cool) (test)    ✅
    
    (wow){thi[is(wow(cool)](test)s} -> (wow) {this} [is(wow(cool)] -> (wow) {this} [is(wow(cool)                        ❌


    The breakout is after seperating and scanning then deleted. It just gets seperated to get checked better.

    First it searches for the first opener.
    Then it goes into the detector
    When finding the same opening brace, it increments a opening int
    When finding the same closing brace, it decrements.
    If decrement is 0, the detector returnes the finished string
    String gets appended in the dstrings
    detector looks in the same string that got returned, if there is still a brace. If yes, it starts from Point 1


    Currently working without loop. Now loop logic and function seperation to reduce lines:
    (Cool){Test[Test2(wow)]fdfdfdf} -> (Cool), {Test[Test2(wow)]fdfdfdf}
    {Test[Test2(wow)]fdfdfdf} -> {Testfdfdfdf}, [Test2(wow)]
*/

char **append_pairs(char **return_pairs, char **pairs, char *filter) {
    int inner = 0, pos = 0, shift = 0;
    char *first = ft_strdup(pairs[0]);
    if (!first)
        return NULL;
    char *second = NULL;
    if (sstrlen(pairs[1]) != 0) {
        second = ft_strdup(pairs[1]);
        if (!second)
            return free(first), NULL;
    }
    char **temp = NULL;
    if (second)
        temp = (char **)malloc(sizeof(char *) * (dstrlen(return_pairs) + 2));
    else
        temp = (char **)malloc(sizeof(char *) * (dstrlen(return_pairs) + 1));
    if (!temp) {
        if (second)
            free(second);
        return free(first), NULL;
    }
    for (; return_pairs[pos]; pos++) {
        if (sstrlen(return_pairs[pos]) != sstrlen(filter)) {
            temp[pos + shift] = return_pairs[pos];
            continue;
        }
        for (inner = 0; return_pairs[pos][inner]; inner++) {
            if (return_pairs[pos][inner] != filter[inner])
                break;
        }
        if (filter[inner]) {
            temp[pos + shift] = return_pairs[pos];
            continue;
        }
        temp[pos + shift] = first;
        if (second) {
            shift++;
            temp[pos + shift] = second;
        }
    }
    temp[pos + shift] = 0;
    free(return_pairs);
    return temp;
}

int seperator(char *argv) {
    if (!argv)
        return 1;
    char **return_pairs = NULL;
    char **pairs = NULL;
    int itteration = 0;
    int return_ = 0;

    return_pairs = (char **)malloc(sizeof(char *) * 2);
    if (!return_pairs)
        return 1;
    return_pairs[0] = argv;
    return_pairs[1] = 0;
    printf("Ret: ");
    for (int i = 0; return_pairs[i]; i++) {
        printf("%s", return_pairs[i]);
        if (return_pairs[i + 1])
            printf(", ");
    }
    printf("\n");
    for (; itteration < __INT_MAX__; itteration++) {
        return_ = 0;
        argv = return_pairs[itteration];
        pairs = split_in_pairs(argv, pairs, &return_);
        if (return_ == 4)
            continue;
        if (!pairs || return_ == 2 || return_ == 3)
            goto cleanup;
        return_ = 0;
        argv = return_pairs[itteration];
        return_pairs = append_pairs(return_pairs, pairs, argv);
        if (!return_pairs) {
            goto cleanup;
        }
        if (precheck(return_pairs[itteration]) != true)
            itteration--;
        dfree(pairs);
        pairs = NULL;
        printf("Ret: ");
        for (int i = 0; return_pairs[i]; i++) {
            printf("%s", return_pairs[i]);
            if (return_pairs[i + 1])
                printf(", ");
        }
        printf("\n");
    }

    dfree(pairs);
    dfree(return_pairs);
    return return_;
    cleanup:
    printf("%i\n", return_);
        dfree(pairs);
        if (return_ != 0)
            return 2;
        for (int i = 0; return_pairs[i]; i++) {
            write(1, "lol\n", 4);
            if (precheck(return_pairs[i]) == false) {
                return 2;
            }
        }
        dfree(return_pairs);
        return return_;
}

int main(int argc, char **argv) {
    if (argc != 2)
        return 1;
    if (seperator(argv[1]) != 0)
        return 1;
    return 0;
}




/// SPLIT THE FUNCTION. Or you will search for the error hours long