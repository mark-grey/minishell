# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/22 11:13:39 by maalexan          #+#    #+#              #
#    Updated: 2023/06/11 11:15:58 by maalexan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME		:=	minishell

# Directories for source, object and libraries
SRC_DIR		:=	./srcs
OBJ_DIR		:=	./objs
BSRC_DIR	:=	./bonus/srcs
HDR_DIR		:=	./incl
FTLIB_DIR	:=	./libs/libft
FTLIB		:=	$(FTLIB_DIR)/libft.a

# Compilation flags
CFLAGS		:=	-Wall -Wextra -Werror -I $(HDR_DIR)
BCFLAGS		:=	-Wall -Wextra -Werror -I ./bonus/incl

# Source files
FUN			:=	main.c \
				checkers.c \
				parse_env.c \
				finders.c

# Object files
OBJ			:=	$(FUN:%.c=$(OBJ_DIR)/%.o)
BOBJ		:=	$(BFUN:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ) $(FTLIB)
	cc $(OBJ) $(FTLIB) -lreadline -o $@

$(FTLIB):
	@$(MAKE) -C $(FTLIB_DIR) --silent

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	cc $(CFLAGS) -c $< -o $@

bonus: $(NAMEB)

$(NAMEB): $(BOBJ) $(FTLIB)
	cc $(BOBJ) $(FTLIB) -o $@

$(OBJ_DIR)/%.o: $(BSRC_DIR)/%.c
	@mkdir -p $(@D)
	@cc $(BCFLAGS) -c $< -o $@

val:
	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all ./${NAME}
clean:
	@$(MAKE) -C $(FTLIB_DIR) --silent clean
	@[ -d ./objs ] && rm -rf ./objs || echo Object directory doesn\'t exist

fclean: clean
	@$(MAKE) -C $(FTLIB_DIR) --silent fclean
	@[ -f ./$(NAME) ] && rm $(NAME) || echo Program $(NAME) isn\'t compiled
	@[ -f ./$(NAMEB) ] && rm $(NAMEB)|| echo Bonus $(NAMEB) isn\'t compiled

re: fclean all

.PHONY: all bonus clean fclean re
