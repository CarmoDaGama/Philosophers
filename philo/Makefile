NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS_FILES = actions.c \
	helpers.c \
	initializer.c \
	observer.c \
	threading.c
	
OBJS_FILES = actions.o \
	helpers.o \
	initializer.o \
	observer.o \
	threading.o
	
all: $(NAME)

$(NAME): $(OBJS_FILES)
	$(CC) $(CFLAGS) $(OBJS_FILES) -o $(NAME) philo.c


clean:
	rm -f $(OBJS_FILES)
	
fclean: clean
	rm -f philo

re: fclean all