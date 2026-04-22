NAME = 				codexion
CC = 				cc
CFLAGS = 			-Wall -Wextra -Werror -fsanitize=thread -g

INCLUDE = 			-I$/include

SRCS_DIR = 			sources
C_FILES = 			main.c \
		  			parser.c \
					ft_atol.c \
					threads.c \
					coders.c \
					monitor.c

SRC = 				$(addprefix $(SRCS_DIR)/, $(C_FILES))

OBJS_DIR = 			obj
OBJ = 				$(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRC))

.PHONY: 			all clean fclean re

all: 				$(NAME)

$(NAME): 			$(OBJ)
		 			$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c
					mkdir -p $(dir $@)
					$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
					rm -rf $(OBJS_DIR)
					@clear

fclean: 			clean
					rm -f $(NAME)

re: 				fclean all
