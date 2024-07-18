// The header file for a Numbers module
// The key functionality of this module is to allow the storing
// of numbers as fractions instead of decimals
// 
// Developed by Fayzulloh Ergashev
#ifndef NUMBERH
# define NUMBERH
# include <stdbool.h>

struct Number {
    int num;
    int denom;
};

// Allocates memory: client needs to free
struct Number * num_from_str(char * str);

// Allocates memory: client needs to free
struct Number * create_number(int num, int denom);

void print_number(struct Number * n);

// Allocates memory: client needs to free
struct Number * multiply_number(struct Number * n1, struct Number * n2);

// Allocates memory: client needs to free
struct Number * divide_number(struct Number * n1, struct Number * n2);

// Allocates memory: client needs to free
struct Number * add_number(struct Number * n1, struct Number * n2);

// Allocates memory: client needs to free
struct Number * subtract_number(struct Number * n1, struct Number * n2);

bool num_equal(struct Number * n1, struct Number * n2);

// Allocates memory: client needs to free
char * str_from_num(struct Number * n);

#endif