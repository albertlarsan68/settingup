##
## EPITECH PROJECT, 2023
## my_ls
## File description:
## Builds stuff
##

CWD != pwd

SRCS = main.c board.c

TESTS_SRCS =

OBJS = $(SRCS:.c=.o)

TESTS_OBJS = $(TESTS_SRCS:.c=.o)

export CFLAGS += -Wall -Wextra -Wpedantic -Werror -march=native -Ofast -flto\
	-Wno-error=missing-profile #-fsanitize=address,undefined

export CPPFLAGS += -I $(CWD)/include/

export ARFLAGS = -rvDsP

export LDFLAGS += -Llib -Ofast -flto -march=native #-fsanitize=address,undefined

LDLIBS += -lmy

NAME = setting_up

all: build

build:
	$(MAKE) fclean
	CFLAGS="-fprofile-generate" LDFLAGS="-fprofile-generate" $(MAKE) $(NAME)
	ls example_files/maps/ | xargs -I {} ./$(NAME) example_files/maps/{} > /dev/null
	./$(NAME) 10000 ".....ooooo.o.o.oooo.o.o.oooo.o.oooo....." > /dev/null
	$(MAKE) profclean
	CFLAGS="-fprofile-use" LDFLAGS="-fprofile-use" $(MAKE) $(NAME)

.PHONY: clean fclean re all build tests_run libbuild

$(NAME): $(OBJS) lib/libmy.a
	$(CC) $(LDFLAGS) $(OBJS) -o $@ $(LOADLIBES) $(LDLIBS)

tests_run: unit_tests
	./unit_tests

lib/libmy.a: lib/my/libmy.a
	$(AR) $(ARFLAGS) --thin $@ $^


lib/my/libmy.a: | libbuild

libbuild:
	$(MAKE) -C lib/my

unit_tests: CFLAGS += --coverage
unit_tests: CPPFLAGS += -DUNIT_TESTS -D "static=" -D "main=my_main"
unit_tests: fclean .WAIT $(TESTS_OBJS) $(OBJS) lib/libmy.a
	$(CC) $(LDFLAGS) $(OBJS) $(TESTS_OBJS) --coverage \
	-o unit_tests $(LOADLIBES) $(LDLIBS) -lcriterion

%.d: %.c
	@set -e; rm -f $@; \
	$(CC) -M $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

include $(SRCS:.c=.d)
include $(TESTS_SRCS:.c=.d)

profclean: clean
	$(MAKE) -C lib/my fclean
	rm -f unit_tests $(NAME) lib/libmy.a

fclean: profclean
	find -type f -name "*.gc*" -delete

clean:
	$(MAKE) -C lib/my clean
	rm -f $(OBJS) $(SRCS:.c=.d) $(TESTS_OBJS) $(TESTS_SRCS:.c=.d)

re:
	$(MAKE) fclean
	$(MAKE) all
