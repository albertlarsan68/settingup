/*
** EPITECH PROJECT, 2023
** myprintf
** File description:
** Consts for the printf family of functions
*/

#include "vgprintf.h"
#include <my_printf.h>

/**
 * A two-dimensional array that maps the pair <current_state><new_char> to the
 * new state.
 *
 * If the state is illegal or not implemented yet, the behavior is undefined.
 */
const unsigned int STATES[][INDEX_STATE('z') + 1] = {
    [BARE] = {[INDEX_STATE('A')] = DHEXA,
        [INDEX_STATE('E')] = EXP,
        [INDEX_STATE('F')] = DOUBLE,
        [INDEX_STATE('G')] = EXACT,
        [INDEX_STATE('L')] = BIGLPRE,
        [INDEX_STATE('X')] = HEXA,
        [INDEX_STATE('a')] = DHEXA,
        [INDEX_STATE('c')] = CHAR,
        [INDEX_STATE('d')] = INT,
        [INDEX_STATE('e')] = EXP,
        [INDEX_STATE('f')] = DOUBLE,
        [INDEX_STATE('g')] = EXACT,
        [INDEX_STATE('h')] = HPRE,
        [INDEX_STATE('i')] = INT,
        [INDEX_STATE('j')] = JPRE,
        [INDEX_STATE('l')] = LPRE,
        [INDEX_STATE('n')] = INTPTR,
        [INDEX_STATE('o')] = OCTAL,
        [INDEX_STATE('p')] = PTR,
        [INDEX_STATE('s')] = STRING,
        [INDEX_STATE('t')] = TPRE,
        [INDEX_STATE('u')] = UINT,
        [INDEX_STATE('x')] = HEXA,
        [INDEX_STATE('z')] = ZPRE},
    [BIGLPRE] = {[INDEX_STATE('A')] = LDHEXA,
        [INDEX_STATE('E')] = LEXP,
        [INDEX_STATE('F')] = LDOUBLE,
        [INDEX_STATE('G')] = LEXACT,
        [INDEX_STATE('a')] = LDHEXA,
        [INDEX_STATE('e')] = LEXP,
        [INDEX_STATE('f')] = LDOUBLE,
        [INDEX_STATE('g')] = LEXACT},
    [HHPRE] = {[INDEX_STATE('X')] = UCHEXA,
        [INDEX_STATE('d')] = SCHAR,
        [INDEX_STATE('i')] = SCHAR,
        [INDEX_STATE('n')] = SCPTR,
        [INDEX_STATE('o')] = UCOCT,
        [INDEX_STATE('u')] = UCHAR,
        [INDEX_STATE('x')] = UCHEXA},
    [HPRE] = {[INDEX_STATE('X')] = USHEXA,
        [INDEX_STATE('d')] = SHORT,
        [INDEX_STATE('h')] = HHPRE,
        [INDEX_STATE('i')] = SHORT,
        [INDEX_STATE('n')] = SPTR,
        [INDEX_STATE('o')] = USOCT,
        [INDEX_STATE('u')] = USHORT,
        [INDEX_STATE('x')] = USHEXA},
    [JPRE] = {[INDEX_STATE('X')] = UMHEXA,
        [INDEX_STATE('d')] = INTMAX,
        [INDEX_STATE('i')] = INTMAX,
        [INDEX_STATE('n')] = SMPTR,
        [INDEX_STATE('o')] = UMOCT,
        [INDEX_STATE('u')] = UINTMAX,
        [INDEX_STATE('x')] = UMHEXA},
    [LLPRE] = {[INDEX_STATE('d')] = LONGLONG,
        [INDEX_STATE('i')] = LONGLONG,
        [INDEX_STATE('u')] = ULONGLONG,
        [INDEX_STATE('n')] = LLPTR,
        [INDEX_STATE('o')] = ULLOCT,
        [INDEX_STATE('x')] = ULLHEXA,
        [INDEX_STATE('X')] = ULLHEXA},
    [LPRE] = {[INDEX_STATE('X')] = ULHEXA,
        [INDEX_STATE('d')] = LONG,
        [INDEX_STATE('i')] = LONG,
        [INDEX_STATE('l')] = LLPRE,
        [INDEX_STATE('n')] = LPTR,
        [INDEX_STATE('o')] = ULOCT,
        [INDEX_STATE('u')] = ULONG,
        [INDEX_STATE('x')] = ULHEXA},
    [TPRE] = {[INDEX_STATE('X')] = UDHEXA,
        [INDEX_STATE('d')] = PTRDIFF,
        [INDEX_STATE('i')] = PTRDIFF,
        [INDEX_STATE('n')] = DPTR,
        [INDEX_STATE('o')] = UDOCT,
        [INDEX_STATE('u')] = UPTRDIFF,
        [INDEX_STATE('x')] = UDHEXA},
    [ZPRE] = {[INDEX_STATE('X')] = UZHEXA,
        [INDEX_STATE('d')] = SSIZE,
        [INDEX_STATE('i')] = SSIZE,
        [INDEX_STATE('n')] = ZPTR,
        [INDEX_STATE('o')] = UZOCT,
        [INDEX_STATE('u')] = SIZE,
        [INDEX_STATE('x')] = UZHEXA},
};

/**
 * Array of handlers, indexed by the final state
 */
const handler_t HANDLERS[] = {
    [CHAR] = put_char,
    [DPTR] = save_dptr,
    [HEXA] = print_uintmax_x,
    [INTMAX] = print_intmax,
    [INTPTR] = save_intptr,
    [INT] = print_intmax,
    [LLPTR] = save_llptr,
    [LONGLONG] = print_intmax,
    [LONG] = print_intmax,
    [LPTR] = save_lptr,
    [OCTAL] = print_uintmax_o,
    [PTRDIFF] = print_intmax,
    [PTR] = print_ptr,
    [SCHAR] = print_intmax,
    [SCPTR] = save_scptr,
    [SHORT] = print_intmax,
    [SIZE] = print_uintmax,
    [SMPTR] = save_smptr,
    [SPTR] = save_sptr,
    [SSIZE] = print_intmax,
    [STRING] = put_string,
    [UCHAR] = print_uintmax,
    [UCHEXA] = print_uintmax_x,
    [UCOCT] = print_uintmax_o,
    [UDHEXA] = print_uintmax_x,
    [UDOCT] = print_uintmax_o,
    [UINTMAX] = print_uintmax,
    [UINT] = print_uintmax,
    [ULHEXA] = print_uintmax_x,
    [ULLHEXA] = print_uintmax_x,
    [ULLOCT] = print_uintmax_o,
    [ULOCT] = print_uintmax_o,
    [ULONGLONG] = print_uintmax,
    [ULONG] = print_uintmax,
    [UMHEXA] = print_uintmax_x,
    [UMOCT] = print_uintmax_o,
    [UPTRDIFF] = print_uintmax,
    [USHEXA] = print_uintmax_x,
    [USHORT] = print_uintmax,
    [USOCT] = print_uintmax_o,
    [UZHEXA] = print_uintmax_x,
    [UZOCT] = print_uintmax_o,
    [ZPTR] = save_zptr,
};

/**
 * Array of fetchers, indexed by the final state
 */
const arg_fetcher_t ARGS[] = {
    [CHAR] = get_char,
    [DHEXA] = get_double,
    [DOUBLE] = get_double,
    [DPTR] = get_ptr,
    [EXACT] = get_double,
    [EXP] = get_double,
    [HEXA] = get_uint,
    [INTMAX] = get_intmax,
    [INTPTR] = get_ptr,
    [INT] = get_int,
    [LDHEXA] = get_ldouble,
    [LDOUBLE] = get_ldouble,
    [LEXACT] = get_ldouble,
    [LEXP] = get_ldouble,
    [LLPTR] = get_ptr,
    [LONGLONG] = get_longlong,
    [LONG] = get_long,
    [LPTR] = get_ptr,
    [OCTAL] = get_uint,
    [PTRDIFF] = get_ptrdiff,
    [PTR] = get_ptr,
    [SCHAR] = get_schar,
    [SCPTR] = get_ptr,
    [SHORT] = get_short,
    [SIZE] = get_size,
    [SMPTR] = get_ptr,
    [SPTR] = get_ptr,
    [SSIZE] = get_ssize,
    [STRING] = get_ptr,
    [UCHAR] = get_uchar,
    [UCHEXA] = get_uchar,
    [UCOCT] = get_uchar,
    [UDHEXA] = get_ptrdiff,
    [UDOCT] = get_ptrdiff,
    [UINTMAX] = get_uintmax,
    [UINT] = get_uint,
    [ULHEXA] = get_ulong,
    [ULLHEXA] = get_ulonglong,
    [ULLOCT] = get_ulonglong,
    [ULOCT] = get_ulong,
    [ULONGLONG] = get_ulonglong,
    [ULONG] = get_ulong,
    [UMHEXA] = get_uintmax,
    [UMOCT] = get_uintmax,
    [UPTRDIFF] = get_ptrdiff,
    [USHEXA] = get_ushort,
    [USHORT] = get_ushort,
    [USOCT] = get_ushort,
    [UZHEXA] = get_size,
    [UZOCT] = get_size,
    [ZPTR] = get_ptr,
};