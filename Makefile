# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/31 20:14:08 by inwagner          #+#    #+#              #
#    Updated: 2023/05/31 21:47:05 by inwagner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/31 19:51:29 by inwagner          #+#    #+#              #
#    Updated: 2023/05/31 20:09:37 by inwagner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAMES
NAME	:=	minishell

# PATHS
SRC		:=	./srcs/
OSRC	:=	./objs/
BSRC	:=	./bonus/srcs/
HDR		:=	./incl/
LSRC	:=	./libs/libft
LBFT	:=	$(LSRC)/libft.a

# FLAGS
CFLAG	:=	-Wall -Wextra -Werror -I $(HDR)

# FILES
FTS		:=	main.c

# OBJECTS
OBJ		:=	$(FTS:%.c=$(OSRC)%.o)

# Commands
all: $(NAME)

# Link objects
$(NAME): $(OBJ) $(LBFT)
	cc $(OBJ) $(LBFT) -o $@

# Compile libraries
$(LBFT):
	@$(MAKE) -C $(LSRC) --silent

# Compile objects
$(OSRC)%.o: $(SRC)%.c
	@mkdir -p $(@D)
	cc $(CFLAG) -c $< -o $@

# Cleaners and Remakers
clean:
	@$(MAKE) -C $(LSRC) --silent clean
	@[ -d $(OSRC) ] && rm -rf $(OSRC) || echo Object directory doesn\'t exist.

fclean: clean
	@$(MAKE) -C $(LSRC) --silent fclean
	@[ -f ./$(NAME) ] && rm $(NAME) || echo Program $(NAME) isn\'t compiled.

re: fclean all

# Recipes
.PHONY: all bonus clean fclean re