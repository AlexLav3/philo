NAME = philo
CC = cc -g -fsanitize=thread
CFLAGS =  -pthread 

SOURCES = main.c init.c utils.c time.c malloc_clean.c simulation.c start_state.c monitor.c
OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all
