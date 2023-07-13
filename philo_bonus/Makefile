COLOUR_GREEN=\033[0;32m
COLOUR_END=\033[0;0m

NAME = philo_bonus
NAME_DEBUG = philo_deb
CC = cc
CFLAGS = -Wall -Wextra -Werror 
THREADS = -fsanitize=thread -pthread

HEADER = -I ./include -I ./philo_bonus.h/include

SRC_DIR = src_bonus
OBJ_DIR = build
SRC_FILES = $(shell find $(SRC_DIR) -name "*.c")
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@echo "Building $(NAME) application"
	@$(CC) $(CFLAGS) $(HEADER) -o $(NAME) $(OBJ_FILES)
	@echo "$(COLOUR_GREEN)BUILD SUCCESSFUL$(COLOUR_END)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(COLOUR_GREEN)Building C object $(notdir $@)$(COLOUR_END)"
	@$(CC) $(CFLAGS) $(HEADER) -c -o $@ $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@echo "Cleaning C objects"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "Cleaning $(NAME) application"
	@rm -f $(NAME)

run: all
	@./$(NAME) $(ARGS)

bonus : all

re: fclean all

.PHONY: clean fclean re


