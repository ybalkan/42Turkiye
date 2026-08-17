NAME		= real_test_binary
NAME_BONUS	= real_test_binary_bonus
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f
OBJ_DIR		= obj

SRCS		= main.c \
			  ft_atoi.c \
			  ft_atoi/00_launcher.c \
			  ft_atoi/01_basic_positive.c \
			  ft_atoi/02_basic_negative.c \
			  ft_atoi/03_zero.c \
			  ft_atoi/04_leading_spaces.c \
			  ft_atoi/05_all_whitespace_chars.c \
			  ft_atoi/06_plus_sign.c \
			  ft_atoi/07_negative_zero.c \
			  ft_atoi/08_int_max.c \
			  ft_atoi/09_int_min.c \
			  ft_atoi/10_number_then_alpha.c \
			  ft_atoi/11_alpha_then_number.c \
			  ft_atoi/12_only_whitespace.c \
			  ft_atoi/13_empty_string.c \
			  ft_atoi/14_only_plus_sign.c \
			  ft_atoi/15_only_minus_sign.c \
			  ft_atoi/16_ws_negative_ws.c \
			  ft_atoi/17_leading_zeros.c

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
