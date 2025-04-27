NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror 

SRC_DIR = src/
OBJ_DIR = obj/

SRC = $(SRC_DIR)philo.c 

OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

INC = -I./include 

HEADERS = include/philo.h

all:$(OBJ_DIR) $(NAME)

$(NAME): $(OBJ)
	$(CC) $^  -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS) Makefile | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR): 
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
run: all
	./$(NAME) 4 800 200 200 5

rundebug: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(NAME)  4 800 200 200 5

re: fclean all

.PHONY: all clean fclean re

