# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/14 14:38:29 by tanas             #+#    #+#              #
#    Updated: 2023/07/14 05:16:34 by sabdelra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COLOURS
GREEN_B = "\033[1;32m"
RED_BI = "\033[1;3;31m"
BLUE_I = "\033[3;34m"
YELLOW = "\033[0;33m"
COLOUR_RESET = "\033[0m"

NAME = minishell
C_FLAGS = -Wall -Wextra -Werror -g3
LIBFT = libft/libft.a
PARSER = src/parser/parser.a
BUILTINS = builtins/builtins.a
LD_FLAGS = -lreadline $(PARSER) $(LIBFT) $(BUILTINS)
INCLUDES = -I include/ -I libft/include

SRCS_DIR = src/
SRCS_LIST = main.c signal.c
SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LIST))

OBJS_DIR = obj/
OBJS_LIST = $(SRCS_LIST:.c=.o)
OBJS = $(addprefix $(OBJS_DIR), $(OBJS_LIST))

all : $(NAME)
test : C_FLAGS += -D TEST
test : all

debug_compile:	C_FLAGS += -D TEST

$(NAME) : $(LIBFT) $(OBJS) parser builtins
	$(CC) $(C_FLAGS) $(INCLUDES) $(OBJS) -o $(NAME) $(LD_FLAGS)
	@echo $(GREEN_B)"$(NAME) is ready. ✅\n"$(COLOUR_RESET)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c $(HEADERS)
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(C_FLAGS) $(INCLUDES) -c $< -o $@
	@echo $(BLUE_I)"Compiling $<."$(COLOUR_RESET)

$(LIBFT) :
	@echo $(YELLOW)"Creating $(LIBFT)"$(COLOUR_RESET)
	@make -sC libft
	@echo $(GREEN_B)"\nLibft is ready. ✅\n"$(COLOUR_RESET)

parser :
	@make -sC src/parser

builtins :
	@make -sC builtins

clean :
	@make clean -sC libft
	@make clean -sC src/parser
	@make clean -sC builtins
	@rm -rf $(OBJS_DIR)
	@echo $(RED_BI)"\nRemoving object directories and files"$(COLOUR_RESET)

fclean : clean
	@rm -f $(NAME)
	@make fclean -sC libft
	@make fclean -sC src/parser
	@make fclean -sC builtins
	@echo $(RED_BI)"Removing $(NAME) and libs\n"$(COLOUR_RESET)

re : fclean all

.PHONY : all clean fclean re builtins parser C_FLAGS
