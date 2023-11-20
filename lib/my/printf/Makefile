##
## EPITECH PROJECT, 2023
## myprintf
## File description:
## Builds stuff
##

SRCS = printf.c vdprintf.c vgprintf.c printf_parsing.c consts.c \
			 getters.c consumers.c integers.c getters2.c integers2.c \
			 getters3.c getters4.c saving.c saprintf.c

OBJS = $(SRCS:.c=.o)

CFLAGS += -ffast-math \
					-fno-associative-math -fsigned-zeros -fno-finite-math-only\

all: build

build: libprintf.a

.PHONY: clean fclean re all build tests_run

libprintf.a: $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

%.d: %.c
	@set -e; rm -f $@; \
	$(CC) -M $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

include $(SRCS:.c=.d)

fclean: clean
	rm -f libprintf.a

clean:
	rm -f $(OBJS) $(SRCS:.c=.d)

re:
	$(MAKE) fclean
	$(MAKE) all
