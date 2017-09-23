# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/20 14:41:19 by vsporer           #+#    #+#              #
#    Updated: 2017/09/22 19:20:14 by vsporer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 			minishell
LIBFT =			libft/libft.a

PATH_LIBFT =	libft/
PATH_SRC =		src/
#PATH_BUILTINS =	$(PATH_SRC)builtins/
PATH_OBJ =		objs/

CC =			gcc -Wall -Werror -Wextra
INC =			-I includes/ -I libft/includes/

SRC =			$(PATH_SRC)main.c\
				$(PATH_SRC)get_env.c\
				$(PATH_SRC)search_var.c\
				$(PATH_SRC)wait_cmd.c

#BUILTINS =		$(PATH_BUILTINS)

OBJ =			$(patsubst $(PATH_SRC)%.c, $(PATH_OBJ)%.o, $(SRC))
#				$(patsubst $(PATH_BUILTINS)%.c, $(PATH_OBJ)%.o, $(BUILTINS))

.PHONY: all clean fclean libft

all: libft $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@echo "Compiling $@ ..."
	@$(CC) $(INC) $^ -o $@
	@echo "\033[32mDone !\033[0m"

$(PATH_OBJ)%.o: $(PATH_SRC)%.c
	@echo "\033[35mCompiling $< to $@\033[0m"
	@mkdir -p $(@D)
	@$(CC) $(INC) -c $< -o $@

$(LIBFT): libft

libft:
	@cd $(PATH_LIBFT) && $(MAKE)

#$(PATH_OBJ)%.o: $(PATH_BUILTINS)%.c
#	@echo "\033[2;35mCompiling $< to $@"\033[0m
#	@mkdir -p $(@D)
#	@$(CC) $(INC) -c $< -o $@

clean:
	@rm -rf $(PATH_OBJ)
	@cd $(PATH_LIBFT) && $(MAKE) clean
	@echo "\033[31mObject files removed.\033[0m"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)
	@echo "\033[31m$(NAME) and $(LIBFT) removed.\033[0m"

test: all
	./minishell

re: fclean all
