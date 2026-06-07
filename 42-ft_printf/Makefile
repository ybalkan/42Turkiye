NAME = libftprintf.a
COMPILER = cc
COMPILER_FLAGS = -Wall -Wextra -Werror
ARCH = ar
ARCH_FLAGS = rcs
OBJDIR = obj
RM = rm -rf
HEADERS = ft_printf.h

SRCS = src/ft_printf.c \
       src/ft_printf_utils.c \
       src/pf_char.c \
       src/pf_string.c \
       src/pf_pointer.c \
       src/pf_int.c \
       src/pf_hex.c

UTLS = utils/ft_strlen.c \
       utils/ft_itoa_base.c \
       utils/write_helpers.c

OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)
UTLS_OBJS = $(UTLS:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(UTLS_OBJS)
	$(ARCH) $(ARCH_FLAGS) $(NAME) $(OBJS) $(UTLS_OBJS)

$(OBJDIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(COMPILER) $(COMPILER_FLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS) $(OBJDIR)

fclean: clean
	@$(RM) $(NAME) $(OBJDIR)

re: fclean all

.PHONY: all clean fclean re
