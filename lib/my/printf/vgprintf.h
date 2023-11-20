/*
** EPITECH PROJECT, 2023
** myprintf
** File description:
** Header for vgprintf
*/

#pragma once
#include <my_printf.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

/**
 * Returns the smallest value between the two arguments, preferring b if they
 * are equal.
 *
 * This macro evaluates the arguments multiple times.
 */
#define MAX(a, b) ((a) > (b)) ? (a) : (b)

/**
 * Returns the smallest value between the two arguments, preferring b if they
 * are equal.
 *
 * This macro evaluates the arguments multiple times.
 */
#define MIN(a, b) ((a) < (b)) ? (a) : (b)

/**
 * Returns the absolute value of the argument
 *
 * This macro evaluates the argument multiple times.
 */
#define ABS(a) ((a) < 0) ? -(a) : (a)

/**
 * Helper macro to simplify the access of the STATE array
 */
#define INDEX_STATE(a) ((a) - 'A')

/**
 * Struct containing the needed state for the good functionning of the vgprintf
 * function.
 */
typedef struct printf_state {
    write_callback_t write;
    void *write_state;
    const char *format;
    va_list *ap;
    int written_len;
    unsigned int flags;
    int width;
    int precision;
    int use_precision;
    unsigned int conv_spec;
} printf_state_t;

/**
 * Union to be able to store the 3 kind of args that can be passed to printf
 */
typedef union arg {
    void *p;
    uintmax_t i;
    long double f;
} arg_t;

/**
 * Advances the format pointer, while parsing a valid format specifier.
 * The pointer must be pointing on the character just after the start %
 */
int parse_percent_action(printf_state_t *state);

/**
 * Prints a string given in argument.p, according to the requirements in state
 *
 * It computes the length of the string, capping it at state->precision if
 * state->use_precision is not 0.
 * It then only does a single call to state->write.
 */
int put_string(printf_state_t *state, arg_t argument);

/**
 * Prints a char given in argument.i.
 *
 * It casts the argument.i value to a char before doing a single call to
 * state->write
 */
int put_char(printf_state_t *state, arg_t argument);

/**
 * Prints an uintmax_t given in argument.i in a given base.
 *
 * This may do multiple calls to state->write
 */
int print_uintmax_base(
    printf_state_t *state, arg_t argument, const char *base, int base_len);

/**
 * Prints an intmax_t given in argument.i.
 *
 * This may do multiple calls to state->write
 */
int print_intmax(printf_state_t *state, arg_t argument);

/**
 * Prints an uintmax_t given in argument.i.
 *
 * This may do multiple calls to state->write
 */
int print_uintmax(printf_state_t *state, arg_t argument);

/**
 * Prints an uintmax_t given in argument.i, in octal.
 *
 * This may do multiple calls to state->write
 */
int print_uintmax_o(printf_state_t *state, arg_t argument);

/**
 * Prints an uintmax_t given in argument.i, in hexadecimal.
 *
 * This may do multiple calls to state->write
 */
int print_uintmax_x(printf_state_t *state, arg_t argument);

/**
 * Prints a void * given in argument.p.
 *
 * This may do multiple calls to state->write
 */
int print_ptr(printf_state_t *state, arg_t argument);

/**
 * Prints a long double given in argument.f.
 *
 * This may do multiple calls to state->write
 */
int print_ldouble_f(printf_state_t *state, arg_t argument);

/**
 * Prints a long double given in argument.f.
 *
 * This may do multiple calls to state->write
 */
int print_ldouble_e(printf_state_t *state, arg_t argument);

/**
 * Prints a long double given in argument.f.
 *
 * This may do multiple calls to state->write
 */
int print_ldouble_g(printf_state_t *state, arg_t argument);

/**
 * Prints a long double given in argument.f.
 *
 * This may do multiple calls to state->write
 */
int print_ldouble_a(printf_state_t *state, arg_t argument);

/**
 * Saves the current number of written bytes to the ptrdiff_t pointed by
 * argument.p
 *
 * It does not call write.
 */
int save_dptr(printf_state_t *state, arg_t argument);

/**
 * Saves the current number of written bytes to the long pointed by argument.p
 *
 * It does not call write.
 */
int save_lptr(printf_state_t *state, arg_t argument);

/**
 * Saves the current number of written bytes to the long long pointed by
 * argument.p
 *
 * It does not call write.
 */
int save_llptr(printf_state_t *state, arg_t argument);

/**
 * Saves the current number of written bytes to the signed char pointed by
 * argument.p
 *
 * It does not call write.
 */
int save_scptr(printf_state_t *state, arg_t argument);

/**
 * Saves the current number of written bytes to the intmax_t pointed by
 * argument.p
 *
 * It does not call write.
 */
int save_smptr(printf_state_t *state, arg_t argument);

/**
 * Saves the current number of written bytes to the short pointed by argument.p
 *
 * It does not call write.
 */
int save_sptr(printf_state_t *state, arg_t argument);

/**
 * Saves the current number of written bytes to the ssize_t pointed by
 * argument.p
 *
 * It does not call write.
 */
int save_zptr(printf_state_t *state, arg_t argument);

/**
 * Saves the current number of written bytes to the int pointed by argument.p
 *
 * It does not call write.
 */
int save_intptr(printf_state_t *state, arg_t argument);

/**
 * Fetches a char value from state->ap, storing it in the i field of the
 * returned union.
 */
arg_t get_char(printf_state_t *state);

/**
 * Fetches a signed char value from state->ap, storing it in the i field of the
 * returned union.
 */
arg_t get_schar(printf_state_t *state);

/**
 * Fetches a short value from state->ap, storing it in the i field of the
 * returned union.
 */
arg_t get_short(printf_state_t *state);

/**
 * Fetches a size_t value from state->ap, storing it in the i field of the
 * returned union.
 */
arg_t get_size(printf_state_t *state);

/**
 * Fetches a ptrdiff_t value from state->ap, storing it in the i field of the
 * returned union.
 */
arg_t get_ptrdiff(printf_state_t *state);

/**
 * Fetches a ssize_t value from state->ap, storing it in the i field of the
 * returned union.
 */
arg_t get_ssize(printf_state_t *state);

/**
 * Fetches an unsigned char value from state->ap, storing it in the i field of
 * the returned union.
 */
arg_t get_uchar(printf_state_t *state);

/**
 * Fetches an unsigned long value from state->ap, storing it in the i field of
 * the returned union.
 */
arg_t get_ulong(printf_state_t *state);

/**
 * Fetches an unsigned long long value from state->ap, storing it in the i
 * field of the returned union.
 */
arg_t get_ulonglong(printf_state_t *state);

/**
 * Fetches an unsigned short value from state->ap, storing it in the i field of
 * the returned union.
 */
arg_t get_ushort(printf_state_t *state);

/**
 * Fetches a void * value from state->ap, storing it in the p field of the
 * returned union.
 */
arg_t get_ptr(printf_state_t *state);

/**
 * Fetches an int value from state->ap, storing it in the i field of the
 * returned union
 */
arg_t get_int(printf_state_t *state);

/**
 * Fetches an unsigned int value from state->ap, storing it in the i field of
 * the returned union
 */
arg_t get_uint(printf_state_t *state);

/**
 * Fetches an intmax_t value from state->ap, storing it in the i field of the
 * returned union
 */
arg_t get_intmax(printf_state_t *state);

/**
 * Fetches an uintmax_t value from state->ap, storing it in the i field of the
 * returned union
 */
arg_t get_uintmax(printf_state_t *state);

/**
 * Fetches a double value from state->ap, storing it in the f field of the
 * returned union
 */
arg_t get_double(printf_state_t *state);

/**
 * Fetches a long double value from state->ap, storing it in the f field of the
 * returned union
 */
arg_t get_ldouble(printf_state_t *state);

/**
 * Fetches a long long value from state->ap, storing it in the i field of the
 * returned union
 */
arg_t get_longlong(printf_state_t *state);

/**
 * Fetches a long value from state->ap, storing it in the i field of the
 * returned union
 */
arg_t get_long(printf_state_t *state);

/* Bitflags that represent the different flags that can be passed to printf.
 *
 * It exploits the fact that all flags are less than 31 bytes away from the
 * space character, to store them compactly in a single unsigned int.
 */

#define LEFT_PAD (1U << ('-' - ' '))
#define MARK_POS (1U << ('+' - ' '))
#define PAD_POS  (1U << (' ' - ' '))
#define ALT_FORM (1U << ('#' - ' '))
#define ZERO_PAD (1U << ('0' - ' '))

/**
 * A mask that ORs all the flags
 */
#define FLAGMASK (LEFT_PAD | MARK_POS | PAD_POS | ALT_FORM | ZERO_PAD)

/**
 * An enum to contain all possible states for the conversion specifier
 */
enum {
    BARE,        /* No chars have been encountered yet */
    BIGLPRE,     /* The `L` modifier has been encountered */
    HHPRE,       /* Two `h` have been encountered */
    HPRE,        /* A single `h` has been encountered */
    JPRE,        /* The `j` modifier has been encountered */
    LLPRE,       /* Two `l` have been encountered */
    LPRE,        /* A single `l` has been encountered */
    TPRE,        /* The `t` modifier has been encountered */
    ZPRE,        /* The `z` modifier has been encountered */
    END_OF_SPEC, /* A value that marks that all following states are final */
    CHAR,        /* This is a char (%c) */
    DHEXA,       /* This is a double, in hexadecimal (%a, %A) */
    DOUBLE,      /* This is a double (%f, %F) */
    DPTR,        /* This is a pointer to a ptrdiff_t (%tn) */
    EXACT,       /* This is an double, in exact notation (%g, %G) */
    EXP,         /* This is a double, in scientific notation (%e, %E) */
    HEXA,        /* This is an unsigned int, in hexadecimal (%x, %X) */
    INT,         /* This is an int (%d, %i) */
    INTMAX,      /* This is an intmax_t (%jd, %ji) */
    INTPTR,      /* This is a pointer to an int (%n) */
    LDHEXA,      /* This is a long double, in hexadecimal (%La, %LA) */
    LDOUBLE,     /* This is a long double (%Lf, %LF) */
    LEXACT,      /* This is a long double, in exact notation (%Lg, %LG) */
    LEXP,        /* This is a long double, in scientific notation (%Le, %LE) */
    LLPTR,       /* This is a pointer to a long long (%lln) */
    LONG,        /* This is a long (%ld, %li) */
    LONGLONG,    /* This is a long long (%lld, %lli) */
    LPTR,        /* This is a pointer to a long (%ln) */
    OCTAL,       /* This is an unsigned int, in octal (%o) */
    PTR,         /* This is a pointer (%p) */
    PTRDIFF,     /* This is a ptrdiff_t (%td, %ti) */
    SCHAR,       /* This is a signed char (%hhd, %hhi) */
    SCPTR,       /* This is a pointer to a signed char (%hhn) */
    SHORT,       /* This is a short int (%hd, %hi) */
    SIZE,        /* This is a size_t (%zu) */
    SMPTR,       /* This is a pointer to an intmax_t (%jn) */
    SPTR,        /* This is a pointer to a signed short (%hn) */
    SSIZE,       /* This is a ssize_t (%zd, %zi) */
    STRING,      /* This is a string (%s) */
    UCHAR,       /* This is an unsigned char (%hhu) */
    UCHEXA,      /* This is an unsigned char, in hexadecimal (%hhx, %hhX) */
    UCOCT,       /* This is an unsigned char, in octal (%hho) */
    UDHEXA,      /* This is an unsigned ptrdiff_t, in hexadecimal (%tx, %tX) */
    UDOCT,       /* This is an unsigned ptrdiff_t, in octal (%to) */
    UINT,        /* This is an unsigned int (%u) */
    UINTMAX,     /* This is an uintmax_t (%ju) */
    ULHEXA,      /* This is an unsigned long, in hexadecimal (%lx, %lX) */
    ULLHEXA,   /* This is an unsigned long long, in hexadecimal (%llx, %llX) */
    ULLOCT,    /* This is an unsigned long long, in octal (%llo) */
    ULOCT,     /* This is an unsigned long, in octal (%lo) */
    ULONG,     /* This is an unsigned long (%lu) */
    ULONGLONG, /* This is an unsigned long long (%llu) */
    UMHEXA,    /* This is a uintmax_t, in hexadecimal (%jx, %jX) */
    UMOCT,     /* This is a uintmax_t, in octal (%jo) */
    UPTRDIFF,  /* This is an unsigned ptrdiff_t (%tu) */
    USHEXA,    /* This is an unsigned short, in hexadecimal (%hx, %hX) */
    USHORT,    /* This is an unsigned short (%hu) */
    USOCT,     /* This is an unsigned short, in octal (%ho) */
    UZHEXA,    /* This is a size_t, in hexadecimal (%zx, %zX) */
    UZOCT,     /* This is a size_t, in octal (%zo) */
    ZPTR,      /* This is a pointer to a size_t (%zn) */
};

/**
 * A two-dimensional array that maps the pair <current_state><new_char> to the
 * new state.
 *
 * If the state is illegal or not implemented yet, the behavior is undefined.
 */
extern const unsigned int STATES[][INDEX_STATE('z') + 1];

/**
 * Callback that does the necessary action based on the state and an arg.
 * It should not use state->ap, as the needed arg (as given by the ARGS
 * array) is bassed in the second argument.
 */
typedef int (*handler_t)(printf_state_t *, arg_t);

/**
 * Array of handlers (see above), indexed by the final state
 */
extern const handler_t HANDLERS[];

/**
 * Callback that returns the correct argument, that will be passed to the
 * corresponding handler_t
 */
typedef arg_t(*arg_fetcher_t)(printf_state_t *);

/**
 * Array of fetchers (see above), indexed by the final state
 */
extern const arg_fetcher_t ARGS[];
