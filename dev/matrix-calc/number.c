// This is a module for a number structure
// The key functionality is that you can store fractions instead of decimals

#include "number.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

static int num_of_digits(int n) {
    if (n < 0) {
        return 1 + num_of_digits(-1 * n);
    } else if (n < 10) {
        return 1;
    } else {
        return 1 + num_of_digits(n / 10);
    }
}

static int ch_to_d(char c) {
    if (c < '0' || c > '9') {
        return 10;
    }
    return c - 48;
}

static int d_to_ch(int n) {
    return n + 48;
}

// Allocates memory: needs to be freed
static char * str_from_int(int n) {
    int temp = n;
    int n_digs = num_of_digits(n);
    if (n < 0) {
        n *= -1;
    }
    char * str = malloc(sizeof(char) * (n_digs + 1));
    for (int i = n_digs - 1; i >= 0; --i) {
        str[i] = d_to_ch(n % 10);
        n /= 10;
    }
    if (temp < 0) {
        str[0] = '-';
    }
    str[n_digs] = '\0';
    return str;
}

int gcd(int m, int n) {
  if ((m % n) == 0) { // Base case
    return n;
  } else {
    return gcd(n, m%n);
  }
}

static struct Number DIVIDE_BY_ZERO = {-2147483648, 0};

void simplify(struct Number * n) {
    int factor = gcd(n->num, n->denom);
    n->num /= factor;
    n->denom /= factor;

    if (n->denom < 0) {
        n->num *= -1;
        n->denom *= -1;
    } 
}

struct Number * create_number(int num, int denom) {
    struct Number * newnum = malloc(sizeof(struct Number));
    newnum->num = num;
    newnum->denom = denom;
    if (num == 0 || denom == 0) {
        return newnum;
    }
    simplify(newnum);
    return newnum;
}

struct Number * num_from_str(char * str) {
    struct Number * new_num = malloc(sizeof(struct Number));
    int i = 1;
    if (str[0] == '-') {
        new_num->num = -1 * ch_to_d(str[1]);
        i = 2;
    } else {
        new_num->num = ch_to_d(str[0]);
    }
    new_num->denom = 1;
    bool fraction = false;

    for (; str[i]; ++i) {
        if (str[i] == '/') {
            fraction = true;
            if (str[i + 1] == '0') {
                new_num = create_number(DIVIDE_BY_ZERO.num, DIVIDE_BY_ZERO.denom);
                return new_num;
            }
            new_num->denom = ch_to_d(str[i + 1]);
            ++i;
        } else if (!fraction) {
            new_num->num = new_num->num * 10 + ch_to_d(str[i]);
        } else {
            new_num->denom = new_num->denom * 10 + ch_to_d(str[i]);
        }
    }
    simplify(new_num);
    return new_num;
}

struct Number * multiply_number(struct Number * n1, struct Number * n2) {
    struct Number * new_num = malloc(sizeof(struct Number));
    new_num->num = n1->num * n2->num;
    new_num->denom = n1->denom * n2->denom;
    simplify(new_num);
    return new_num;
}

struct Number * divide_number(struct Number * n1, struct Number * n2) {
    struct Number * newn2 = create_number(n2->denom, n2->num);
    simplify(newn2);
    struct Number * product = multiply_number(n1, newn2);
    free(newn2);
    return product;
}

struct Number * add_number(struct Number * n1, struct Number * n2) {
    struct Number * sum = malloc(sizeof(struct Number));
    sum->num = n1->num * n2->denom + n2->num * n1->denom;
    sum->denom = n1->denom * n2->denom;
    simplify(sum);
    return sum;
}

struct Number * subtract_number(struct Number * n1, struct Number * n2) {
    struct Number * difference = malloc(sizeof(struct Number));
    struct Number * newn2 = create_number(-1 * n2->num, n2->denom);
    difference = add_number(n1, newn2);
    free(newn2);
    return difference;
}

void print_number(struct Number * num) {
    if (num->denom == 1) {
        printf("%d", num->num);
        return;
    }
    printf("%d / %d", num->num, num->denom);
}

bool num_equal(struct Number * n1, struct Number * n2) {
    return n1->num == n2->num && n1->denom == n2->denom;
}

char * str_from_num(struct Number * n) {
    // If fraction, return string of numerator
    if (n->denom == 1) {
        return str_from_int(n->num);
    }

    // Setup with number of digits of numerator and denominator
    int numerator_digs = num_of_digits(n->num);
    int denom_digs = num_of_digits(n->denom);
    char * numerator_str = str_from_int(n->num);
    char * denominator_str = str_from_int(n->denom);
    char * result = malloc((numerator_digs + denom_digs + 2) * sizeof(char));

    // Fill the first spots with the digits of numerator
    for (int i = 0; i < numerator_digs; ++i) {
        result[i] = numerator_str[i];
    }
    
    result[numerator_digs] = '/';

    // Fill the space after the slash with digits of denom
    for (int i = numerator_digs + 1, j = 0; i < numerator_digs + denom_digs + 2; ++i, ++j) {
        result[i] = denominator_str[j];
    }

    // Free some allocated memory
    free(numerator_str);
    free(denominator_str);

    // Add null char and return result
    result[numerator_digs + denom_digs + 1] = '\0';
    return result;
}