/*
** EPITECH PROJECT, 2023
** myprintf
** File description:
** Header for vdprintf
*/

#pragma once

/**
 * This struct is for keeping the data needed for the my_vdprintf write
 * implementation.
 */
typedef struct my_vdprintf_data {
    /**
     * The file descriptor to write to.
     */
    int fd;
} my_vdprintf_data_t;
