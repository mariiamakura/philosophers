
#include <stddef.h>
#include <limits.h>
#include <printf.h>
#include "util.h"

BOOL is_int(BIG_INT number) {
    return INT_MIN <= number && number <= INT_MAX;
}

BOOL is_white_space(char symbol) {
    return symbol == ' ' || (symbol >= '\t' && symbol <= '\r');
}

BOOL is_number(const char *str) {
    int i = 0;

    while (is_white_space(str[i])) {
        i++;
    }
    while (str[i] == '+' || str[i] == '-') {
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9') {
        i++;
    }

    return str[i] == '\0';
}

BIG_INT parse_number(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int i = 0;
    while (is_white_space(str[i])) {
        i++;
    }
    BOOL is_negative = FALSE;
    while (str[i] == '+' || str[i] == '-') {
        if (str[i] == '-') {
            is_negative = !is_negative;
        }
        i++;
    }
    long long number = 0;
    while (str[i] >= '0' && str[i] <= '9') {
        number = (number * 10) + (str[i] - '0');
        i++;
    }
    return is_negative ? -number : number;
}
