#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "bignum.h"

// panic() is already defined in list.c, so we provide only a declaration here.
void panic(char *s);

// defined in add.s
void add(long a, long b, long carry_in, long *sum, long *carry_out);

struct bignum *bignum_new(long val) {
    struct bignum *v = malloc(sizeof(struct bignum));
    if (v == NULL) panic("out of memory");
    v->bits = new();
    add_tail(v->bits, val);
    return v;
}

char *bignum_to_string(struct bignum *v) {
    assert(v != NULL && size(v->bits) > 0);

    int sz = size(v->bits);
    char *s = malloc(sz*16 + 1);
    if (s == NULL) panic("out of memory");

    int cnt = sprintf(s, "%lX", get(v->bits, sz - 1));
    int i = sz - 2;
    while (i >= 0) {
        cnt += sprintf(s + cnt, "%016lX", get(v->bits, i));
        i--;
    }

    return s;
}

struct bignum *bignum_add(struct bignum *a, struct bignum *b) {
    assert(a != NULL && size(a->bits) > 0 && b != NULL && size(a->bits) > 0);

    long sum = 0;
    long carry_in = 0;
    long carry_out = 0;

    int asz = size(a->bits);
    int bsz = size(b->bits);
    int sz = asz;
    if (bsz > sz) sz = bsz;

    struct bignum *r = bignum_new(0);
    remove_at(r->bits, 0);          // hack to initialise an empty bits linked list

    long val_a, val_b;

    // printf("\n\nadd() [%d, %d | %d]\n", asz, bsz, sz);

    for (int i = 0; i < sz; i++)
    {
        if (i >= asz)   val_a = 0;
        else            val_a = get(a->bits, i);

        if (i >= bsz)   val_b = 0;
        else            val_b = get(b->bits, i);

        sum = 0;    carry_out = 0;

        add(val_a, val_b, carry_in, &sum, &carry_out);
        // printf("\t@ %d -> %lu + %lu + %lu = [%lu]\n", i, val_a, val_b, carry_in, sum);

        add_tail(r->bits, sum);

        carry_in = carry_out;

        // printf("\t  --> {0x%s} | sum=[%lu] | in=%lu out=%lu\n\n", bignum_to_string(r), sum, carry_in, carry_out);
    }

    if (carry_out == 1)     add_tail(r->bits, 1);

    // printf("\treturn: 0x%s\n\n", bignum_to_string(r));

    return r;
}

void bignum_destroy(struct bignum *v) {
    assert(v != NULL);
    destroy(v->bits);
    free(v);
}
