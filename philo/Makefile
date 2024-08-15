NAME = philo
CC = cc
CFLAGS = -Wall -Wextra - Werror
FLAG = -pthread
SRCS = philo.c parsing.c ft_init.c libft.c ft_error.cc
OBJC = $(SRCS:.c=.o)

all:$(NAME)

$(NAME) = $(OBJC)
	@$(CC) $(SRCS) $(CFLAGS) $(FLAG) -o philo
	@echo "executable file is ready"

.c.o:
	$(CC) $(CFLAGS) $(FLAG) -c $< -o $@

clean:
	@rm -f $(OBJC)
	@echo "objects removed"

fclean:
	@rm  -f $(OBJC) $(NAME)
	@echo "objects and executable removed"

re: fclean all