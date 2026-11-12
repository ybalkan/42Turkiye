NAME		= codexion
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pthread
CPPFLAGS	= -Iinc

SRCS		= src/main.c \
			  src/parse.c \
			  src/parse_values.c \
			  src/setup.c \
			  src/setup_objects.c \
			  src/threads.c \
			  src/time.c \
			  src/heap.c \
			  src/heap_utils.c \
			  src/dongle_setup.c \
			  src/dongle_state.c \
			  src/coder.c \
			  src/coder_utils.c \
			  src/acquire.c \
			  src/scheduler.c \
			  src/monitor.c \
			  src/log.c

OBJ_DIR = obj
OBJS    = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re