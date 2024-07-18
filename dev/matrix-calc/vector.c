// This is a module for implementing vectors
// 
// Developed by Fayzulloh
#include <stdlib.h>
#include <stdio.h>
#include "vector.h"
#include "number.h"

struct vector {
    int n;
    struct Number ** vec;
};

struct vector * create_vector(int n) {
    struct vector * v = malloc(sizeof(struct vector));
    v->n = n;
    v->vec = malloc(n * sizeof(struct Number *));
    for (int i = 0; i < n; ++i) {
        v->vec[i] = malloc(sizeof(struct Number));
        v->vec[i] = create_number(0, 0);
    }
    return v;
}

int get_vector_n(struct vector * v) {
    return v->n;
}

struct Number * ith_element(struct vector * v, int i) {
    return v->vec[i];
}

void destroy_vector(struct vector * v) {
    for (int i = 0; i < v->n; ++i) {
        free(v->vec[i]);
    }
    free(v->vec);
    free(v);
}

bool set_vector_element(struct vector * v, int i, struct Number * num) {
    if (i > v->n) {
        return false;
    }
    v->vec[i] = num;
    return true;
}

struct Number * dot_product(struct vector * v1, struct vector * v2) {
    struct Number * result = create_number(0, 1);
    int vsize = v1->n;
    for (int i = 0; i < vsize; ++i) {
        result = add_number(result, multiply_number(v1->vec[i], v2->vec[i]));
    }
    return result;
}

void zeroify_vector(struct vector * v) {
    struct Number * ZERO = create_number(0, 0);
    int vsize = get_vector_n(v);
    for (int i = 0; i < vsize; ++i) {
        if (num_equal(ZERO, ith_element(v, i))) {
            set_vector_element(v, i, create_number(0, 1));
        }
    }
    free(ZERO);
}