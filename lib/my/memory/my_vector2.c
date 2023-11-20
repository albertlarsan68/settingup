/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** My implementation of the vector data structure
*/

#include <my_memory.h>
#include <my_vector.h>
#include <my.h>

void vector_destroy_free(void *element)
{
    my_free(element);
}

void vector_destroy_noop(void *element)
{
    (void) element;
}

void vector_reverse(vector_t *vector)
{
    void *tmp;

    for (size_t it = 0; it < vector->size / 2; it++) {
        tmp = vector->data[it];
        vector->data[it] = vector->data[vector->size - it - 1];
        vector->data[vector->size - it - 1] = tmp;
    }
}
