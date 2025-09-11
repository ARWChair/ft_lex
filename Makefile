SRCS 	= srcs/map.c srcs/options.c srcs/parts.c srcs/stderr.c srcs/stdout.c srcs/strings.c srcs/utils.c main.c
CC  	= cc -g
OBJS	= $(SRCS:.s=.o)
RM		= rm -f
NAME	= ft_lex

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(SRCS) -o $(NAME) 

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(NAME)

re: fclean all