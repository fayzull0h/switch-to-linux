#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t field_element_t;
typedef uint8_t field_logarithm_t;

field_logarithm_t generator_root_exp[32][255];
field_element_t polynomial_coeff[sizeof(field_element_t) * 33] = {0};

typedef struct {
    field_element_t coeff[33];
    unsigned int order;
} polynomial_t;

typedef struct {
    field_element_t *coeff;
    unsigned int order;
} dynamic_polynomial_t;

dynamic_polynomial_t polynomial_create(unsigned int order) {
    dynamic_polynomial_t polynomial;
    polynomial.coeff = malloc(sizeof(field_element_t) * (order + 1));
    polynomial.order = order;
    return polynomial;
}

int copy_array(field_element_t * src, field_element_t * dest, field_element_t len) {
    if (src == NULL || dest == NULL) {
        return -1;
    }

    field_element_t i = 0;
    for (i = 0; i < len; i++) {
        dest[i] = src[i];
    }
    return i + 1;
}

polynomial_t create_from_roots(unsigned int nroots) {
    polynomial_t poly = {.order = nroots + 1};
    printf("new poly at: %p\n", &poly);
    field_element_t coeffs[3] = {1, 2, 3};
    copy_array(coeffs, poly.coeff, nroots + 1);
    return poly;
}

int main() {
    field_element_t coeffs[5] = {1, 2, 3, 4, 5};

    dynamic_polynomial_t poly1 = polynomial_create(4);
    polynomial_t poly2 = {.order = 4};
    polynomial_t poly3 = {.order = 4};
    copy_array(coeffs, poly3.coeff, 5);
    polynomial_t poly4 = {.order = 4};
    poly4 = poly3;
    //copy_array(poly4.coeff, poly3.coeff, 33);

    copy_array(coeffs, poly1.coeff, poly1.order + 1);
    copy_array(coeffs, poly2.coeff, poly2.order + 1);

    printf("poly1 address: %p\n", poly1.coeff);
    printf("poly2 address: %p\n", poly2.coeff);
    printf("poly3 address: %p\n", poly3.coeff);
    printf("poly4 address: %p\n", poly4.coeff);

    printf("poly4: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", poly4.coeff[i]);
    }
    printf("\n");

    printf("poly2: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", poly2.coeff[i]);
    }
    printf("\n");

    polynomial_t test_create = create_from_roots(2);
    printf("test_create polynomial: %p\n", &test_create);

    /*
    field_logarithm_t ** generator_dynamic = malloc(32 * sizeof(field_logarithm_t *));
    for (int i = 0; i < 32; i++) {
        generator_dynamic[i] = malloc(255 * sizeof(field_logarithm_t));
    }

    field_logarithm_t * generator_static = generator_root_exp;

    printf("Dynamic size: %d\n", generator_dynamic);
    printf("Static size: %d\n", generator_static);
    */

    free(poly1.coeff);
}