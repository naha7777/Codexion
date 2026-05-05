NAME = 				codexion
CC = 				cc
CFLAGS = 			-Wall -Wextra -Werror -pthread -g

INCLUDE = 			-I$/include

SRCS_DIR = 			sources
C_FILES = 			main.c \
		  			init/parser.c \
					init/fill_struct.c \
					init/fill_heaps.c \
					utils/ft_atol.c \
					utils/ft_calloc.c \
					utils/time.c \
					cleaner/clean.c \
					cleaner/destroy.c \
					simulation/monitor.c \
					simulation/routine.c \
					simulation/dongle.c \
					simulation/utils.c \
					simulation/heap.c \
					simulation/algo.c

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
