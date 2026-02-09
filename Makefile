NAME		=	philo
CC			=	cc
CFLAGS		=	-pthread -Wall -Wextra -Werror
SRCS		=	clean.c \
				eating_habits.c \
				main.c \
				mangia.c \
				monitoring.c \
				set_the_table.c \
				utils.c
OBJ_DIR		=	build
OBJS		=	$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all:		$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean:		clean
	@rm -f $(NAME)

re:			fclean all
