##
## EPITECH PROJECT, 2023
## libmy
## File description:
## Builds stuff
##

SRCS = my_memory.c

OBJS = $(SRCS:.c=.o)

all: build

build: libmemory.a

.PHONY: clean fclean re all build tests_run

libmemory.a: $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

%.d: %.c
	@set -e; rm -f $@; \
	$(CC) -M $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

include $(SRCS:.c=.d)

fclean: clean
	rm -f libmemory.a

clean:
	rm -f $(OBJS) $(SRCS:.c=.d)

re:
	$(MAKE) fclean
	$(MAKE) all
