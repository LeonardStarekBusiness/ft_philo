NAME = philo

CFLAGGEN = -Wall -Wextra -Werror -g

CC = cc

QUELLE_DATEIEN = time.c spawn.c philo_utils.c actions.c philo.c

OBJEKT_DATEIEN = $(QUELLE_DATEIEN:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGGEN) -c $< -o $@

$(NAME): $(OBJEKT_DATEIEN)
	$(CC) $(OBJEKT_DATEIEN) -o $(NAME)

clean: 
	rm -f $(OBJEKT_DATEIEN)

fclean: clean 
	rm -f $(NAME)

re: fclean all

.PHONY: all clean flcean re