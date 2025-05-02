NAME = cub3D
CC = cc
FLAGS = -Wall -Wextra -Werror -g3
INCLUDES = -I./includes
SRCS_DIR = srcs
OBJS_DIR = objs
SRCS =  $(SRCS_DIR)/main.c \
		$(SRCS_DIR)/get_next_line/get_next_line_utils.c \
		$(SRCS_DIR)/get_next_line/get_next_line.c \
		$(SRCS_DIR)/utils/ft_split.c \
		$(SRCS_DIR)/utils/str_utils.c

OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) -o $(NAME) $(OBJS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
		@mkdir -p $(OBJS_DIR)
		@mkdir -p $(OBJS_DIR)/get_next_line
		@mkdir -p $(OBJS_DIR)/utils
		$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
		rm -f $(OBJS)
		rm -rf $(OBJS_DIR)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
