# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: Ceren Kurt <cerkurt@student.codam.nl>        +#+                      #
#                                                    +#+                       #
#    Created: 2025/12/27 21:52:30 by cerkurt       #+#    #+#                  #
#    Updated: 2025/12/30 15:17:35 by cerkurt       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                           MAKE FILE FOR PUSH_SWAP                            #
# **************************************************************************** #

# **************************************************************************** #
#                                BASH COMMANDS                                 #
# **************************************************************************** #

# make          builds push_swap.a with given sources
# make clean    remove .o
# make fclean   remove .o and libft.a
# make re       full rebuild

# **************************************************************************** #



# **************************************************************************** #
#                 OUTPUT NAME - COMPILE FLAGS - CREATION COMMAND               #
# **************************************************************************** #

NAME        := push_swap
CC          := cc
CFLAGS      := -Wall -Wextra -Werror
RM          := rm -f
LIBFT_DIR   := libft
LIBFT       := $(LIBFT_DIR)/libft.a
INCLUDES	:= -I. -I$(LIBFT_DIR)

# **************************************************************************** #



# **************************************************************************** #
#                        PUSH_SWAP MANDATORY SOURCES                           #
# **************************************************************************** #

MAND_SRCS	:= \
	01_operations/opr_push.c \
	01_operations/opr_reverse_rotate.c \
	01_operations/opr_rotate.c \
	01_operations/opr_swap.c \
	02_moves/apply_calculated_moves.c \
	02_moves/cost_calculations.c \
	02_moves/insertions_and_moves.c \
	03_sorting/sort_four_five_a.c \
	03_sorting/sort_three_a.c \
	03_sorting/sort_three_b.c \
	03_sorting/sort_total_ab.c \
	03_sorting/sort_two_ab.c \
	04_parsing_and_main/argument_handling.c \
	04_parsing_and_main/free_and_error_exits.c \
	04_parsing_and_main/input_checks.c \
	04_parsing_and_main/ranks_and_stacks.c \
	04_parsing_and_main/push_swap.c \

# **************************************************************************** #



# **************************************************************************** #
#                             COMPILATION AND OUTPUT                           #
# **************************************************************************** #
SRCS        := $(MAND_SRCS)

OBJS        := $(SRCS:.c=.o)

# **************************************************************************** #



# **************************************************************************** #
#                       BASH COMMANDS AND TERMINAL MESSAGES                    #
# **************************************************************************** #

all: $(NAME)
$(NAME): $(LIBFT) $(OBJS)
	@echo "Building $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) \
		&& echo "Successfully created $(NAME)!" \
		|| (echo "Failed to build $(NAME)!"; exit 1)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	@$(RM) $(OBJS)
	make -C $(LIBFT_DIR) clean
	@echo "Objects are removed!"

fclean: clean
	@$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean
	@echo "Cleanup complete!"

re: fclean all

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: all clean fclean re

# **************************************************************************** #