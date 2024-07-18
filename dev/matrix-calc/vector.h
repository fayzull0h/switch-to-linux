// This is the interface for a module that implements vector functionality
//
// Developed by Fayzulloh Ergashev

#include "number.h"
#ifndef VECTORH
# define VECTORH

struct vector;

// create_vector(n) allocates memory for a vector of size n
//  and returns a pointer to the memory
// effects: allocates memory, needs to be freed (destroy_vector)
struct vector * create_vector(int n);

// get_vector_n(v) returns the size of v (i.e. v->n)
int get_vector_n(struct vector * v);

// ith_element(v, i) returns the i'th element of v (i.e. v->vec[i])
// Note: do not free result
struct Number * ith_element(struct vector * v, int i);

// destroy_vector(v) frees all the memory inside v
// effects: deallocates memory
void destroy_vector(struct vector * v);

// set_vector_element(v, i, num) sets the ith_element of v to num
//  returns true if successful
bool set_vector_element(struct vector * v, int i, struct Number * num);

// dot_product(v1, v2) calculates the dot product of the two vectors
//  returns a Number
// effects: allocates memory, needs to be freed
struct Number * dot_product(struct vector * v1, struct vector * v2);

// zeroify_vector(v) turns all ZERO Numbers into create_number(0, 1)
// effects: modifies v
void zeroify_vector(struct vector * v);
#endif