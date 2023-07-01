COLOUR_GREEN=\033[0;32m
COLOUR_END=\033[0;0m

NAME = philo
NAME_DEBUG = philo_deb
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread

HEADER = -I ./include -I ./philo.h/include

SRC_DIR = src
OBJ_DIR = build/objects
TRG_DIR = build/targets
SRC_FILES = $(shell find $(SRC_DIR) -name "*.c")
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

all: $(NAME)

$(NAME): $(OBJ_FILES) $(TRG_DIR)
	@echo "Building $(NAME) application"
	@$(CC) $(CFLAGS) $(HEADER) -o $(TRG_DIR)/$(NAME) $(OBJ_FILES)
	@echo "$(COLOUR_GREEN)BUILD SUCCESSFUL$(COLOUR_END)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(COLOUR_GREEN)Building C object $(notdir $@)$(COLOUR_END)"
	@$(CC) $(CFLAGS) $(HEADER) -c -o $@ $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(TRG_DIR):
	@mkdir -p $(TRG_DIR)

clean:
	@echo "Cleaning C objects"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "Cleaning $(NAME) application"
	@rm -rf $(TRG_DIR)

run: all
	@./$(TRG_DIR)/$(NAME) $(ARGS)


re: fclean all

.PHONY: clean fclean re


