NAME        = push_swap
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -Iincludes

SRCS_DIR    = srcs/
OBJS_DIR    = objs/

MAIN_FILES  = main/main.c main/init.c main/exit.c main/flag.c main/bench.c
PARS_FILES  = parsing/parser.c parsing/check.c parsing/string.c parsing/help.c
OPS_FILES   = ops/push.c ops/swap.c ops/rotate.c ops/rrotate.c
ALGO_FILES  = algo/engine.c algo/hcoded.c
UTIL_FILES  = utils/stack.c utils/algo.c utils/node.c utils/disorder.c

SRC_FILES   = $(MAIN_FILES) $(PARS_FILES) $(OPS_FILES) $(ALGO_FILES) $(UTIL_FILES)

SRCS        = $(addprefix $(SRCS_DIR), $(SRC_FILES))
OBJS        = $(addprefix $(OBJS_DIR), $(SRC_FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
