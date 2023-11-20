/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** My implementation of the vector data structure
*/

#include "my_printf.h"
#include <my_memory.h>
#include <my_vector.h>
#include <my.h>

static int vector_grow_alloc_if_needed(vector_t *vector)
{
    if (vector->size != vector->capacity)
        return 0;
    vector->capacity = vector->capacity ? vector->capacity * 2 : 1;
    vector->data =
        my_reallocarray(vector->data, vector->capacity, sizeof(void *));
    return 0;
}

vector_t *vector_construct(vector_destroy_method destroy_method)
{
    vector_t *vector = my_calloc(1, sizeof(vector_t));

    vector->destroy_method =
        destroy_method ? destroy_method : vector_destroy_noop;
    return vector;
}

int vector_destroy(vector_t *vector)
{
    if (vector->data) {
        for (size_t it = 0; it < vector->size; it++)
            vector->destroy_method(vector->data[it]);
        my_free(vector->data);
    }
    my_free(vector);
    return 0;
}

int vector_push_back(vector_t *vector, void *element)
{
    if (!vector)
        return -1;
    vector_grow_alloc_if_needed(vector);
    vector->data[vector->size] = element;
    vector->size++;
    return 0;
}

void *vector_get(vector_t *vector, size_t index)
{
    if (!vector || index >= vector->size)
        return NULL;
    return vector->data[index];
}

static int swap_if_needed(void **a, void **b, int swap)
{
    void *tmp;

    if (swap == 0)
        return 0;
    tmp = *a;
    *a = *b;
    *b = tmp;
    return 1;
}

void vector_sort(vector_t *vector, int (*cmp)(const void *, const void *))
{
    int nb_swap = 1;

    if (vector->size < 2)
        return;
    while (nb_swap) {
        nb_swap = 0;
        for (size_t it = 0; it < vector->size - 1; it++) {
            nb_swap += swap_if_needed(&vector->data[it], &vector->data[it + 1],
                cmp(vector->data[it], vector->data[it + 1]) > 0);
        }
    }
}
