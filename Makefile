NAME = philo

CC = cc
CFLAGS = -g -Wall -Wextra -Werror

SRCS = src/main.c \
	src/parsing.c \
	src/utils.c \
	src/actions.c \
	src/monitor.c \
	src/string_utils.c

OBJDIR = obj
OBJS = $(patsubst src/%.c,$(OBJDIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -pthread -o $(NAME)

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -pthread -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re