#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "list.h"

void panic(char *s) {
    fprintf(stderr, "%s\n", s);
    exit(1);
}

struct list *new() {
    struct list *list;

    list = (struct list *) malloc(sizeof(struct list));

    if (list == NULL)   panic("CRITICAL ERROR\n");

    list->size = 0;
    list->head = NULL;
    list->tail = NULL;

    return list;
}

void destroy(struct list *l) {
    assert(l != NULL);

    struct node *node = l->head;
    struct node *next_copy = NULL;

    while (node != NULL)
    {
        next_copy = node->next;
        free(node);
        node = next_copy;
    }

    free(l);
}

int size(struct list *l) {
    assert(l != NULL);

    return l->size;
}

void add_tail(struct list *l, long val) {
    assert(l != NULL);

    struct node *new_node;

    new_node = (struct node *) malloc(sizeof(struct node));

    if (new_node == NULL)   panic("CRITICAL ERROR\n");

    struct node *former_tail = l->tail;

    new_node->val = val;
    new_node->next = NULL;
    new_node->prev = former_tail;

    if (&former_tail->val == NULL)  // check if this is the first node to be added
    {
        l->head = new_node;  // set the head of the list to be the new node
    } else
    {
        former_tail->next = new_node;  // set the next pointer of the former tail node to the new node
    }

    l->size += 1;
    l->tail = new_node;
}

long remove_at(struct list *l, int index) {
    assert(l != NULL && index >= 0 && index < l->size);

    int i = 0;
    struct node *node = l->head;
    struct node *prev_node = NULL;
    struct node *next_node = node->next;

    while (node != NULL)
    {
        if (i == index)
        {
            // check if head
            if (i == 0)     l->head = node->next;

            else {
                prev_node->next = node->next;
                next_node->prev = prev_node;

                // check if tail
                if (i == l->size - 1)   l->tail = node->prev;
            }

            l->size -= 1;

            long val = node->val;
            free(node);

            return val;
        }

        prev_node = node;
        node = node->next;
        next_node = node->next;
        i++;
    }

    return 0;
}

long get(struct list *l, int index) {
    assert(l != NULL && index >= 0 && index < l->size);

    int i = 0;
    struct node *node = l->head;

    while (node != NULL)
    {
        if (i == index)     return node->val;
        
        node = node->next;
        i++;
    }

    return -1;
}
