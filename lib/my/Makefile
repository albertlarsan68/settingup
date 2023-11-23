##
## EPITECH PROJECT, 2023
## libmy
## File description:
## Builds stuff
##

LIBS = memory

LIBSOBJS = $(foreach lib,$(LIBS),$(lib)/lib$(lib).a)

SRCS = utils.c

OBJS = $(SRCS:.c=.o)

all: libmy.a

.PHONY: clean fclean re all $(LIBS:%=build-%)

libmy.a: $(LIBSOBJS) $(OBJS)
	$(AR) $(ARFLAGS) --thin $@ $^

printf/libprintf.a: build-printf

memory/libmemory.a: build-memory

$(LIBS:%=build-%):
	$(MAKE) -C $(@:build-%=%)

$(LIBS:%=clean-%):
	$(MAKE) -C $(@:clean-%=%) clean

$(LIBS:%=fclean-%):
	$(MAKE) -C $(@:fclean-%=%) fclean

clean: $(LIBS:%=clean-%)
	rm -f $(OBJS) $(SRCS:.c=.d)

fclean: $(LIBS:%=fclean-%)
	rm -f libmy.a
