NAME		= test_binary
NAME_BONUS	= test_binary_bonus
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f
OBJ_DIR		= obj

SRCS		= main.c \
			  dummy_tests/00_launcher.c \
			  dummy_tests/01_ok_test.c \
			  dummy_tests/02_ko_test.c \
			  dummy_tests/03_segv_test.c \
			  dummy_tests/04_bus_test.c \
			  dummy_tests/05_abrt_test.c \
			  dummy_tests/06_fpe_test.c \
			  dummy_tests/07_pipe_test.c \
			  dummy_tests/08_ill_test.c \
			  dummy_tests/09_timeout_test.c

OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
BONUS_OBJS	= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.bonus.o))

INC_DIR		= ../framework/mandatory
LIB_DIR		= ../framework/mandatory

INC_BONUS	= ../framework/bonus
LIB_BONUS	= ../framework/bonus

all: $(NAME) $(NAME_BONUS)

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIB_DIR) > /dev/null
	$(CC) $(CFLAGS) $(OBJS) -I$(INC_DIR) -L$(LIB_DIR) -lunit -o $(NAME)

$(NAME_BONUS): $(BONUS_OBJS)
	@$(MAKE) -C $(LIB_BONUS) > /dev/null
	$(CC) $(CFLAGS) $(BONUS_OBJS) -I$(INC_BONUS) -L$(LIB_BONUS) -lunit -o $(NAME_BONUS)

test:
	@test -f $(NAME) || (echo "Error: Run 'make' first." && exit 1)
	./$(NAME)

bonus:
	@test -f $(NAME_BONUS) || (echo "Error: Run 'make' first." && exit 1)
	./$(NAME_BONUS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR)/%.bonus.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -DBONUS -I$(INC_BONUS) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)
	@$(MAKE) -C $(LIB_DIR) clean > /dev/null
	@$(MAKE) -C $(LIB_BONUS) clean > /dev/null

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)
	@$(MAKE) -C $(LIB_DIR) fclean > /dev/null
	@$(MAKE) -C $(LIB_BONUS) fclean > /dev/null

re: fclean all

.PHONY: all test bonus clean fclean re
