# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/20 14:41:19 by vsporer           #+#    #+#              #
#    Updated: 2017/09/16 02:57:57 by vsporer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 			minishell
LIBFT =			libft/libft.a

PATH_LIBFT =	libft/
PATH_SRC =		src/
PATH_BUILTINS =	$(PATH_SRC)builtins/
PATH_OBJ =		objs/

CC =			gcc -Wall -Werror -Wextra
INC =			-I includes/ -I libft/includes/

SRC =			$(PATH_SRC)main.c

BUILTINS =		$(PATH_BUILTINS)

OBJ =			$(patsubst $(PATH_SRC)%.c, $(PATH_OBJ)%.o, $(SRC))
				$(patsubst $(PATH_BUILTINS)%.c, $(PATH_OBJ)%.o, $(BUILTINS))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@echo "Compiling $@ ..."
	@$(CC) $(INC) $^ -o $@
	@echo "Done !"

$(LIBFT):
	@cd $(PATH_LIBFT) && $(MAKE)

$(PATH_OBJ)%.o: $(PATH_SRC)%.c
	@echo "Compiling $< to $@"
	@mkdir -p $(@D)
	@$(CC) $(INC) -c $< -o $@

$(PATH_OBJ)%.o: $(PATH_BUILTINS)%.c
	@echo "Compiling $< to $@"
	@mkdir -p $(@D)
	@$(CC) $(INC) -c $< -o $@

clean:
	@rm -rf $(PATH_OBJ)
	@cd $(PATH_LIBFT) && $(MAKE) clean
	@echo "Object files removed."

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)
	@echo "$(NAME) and $(LIBFT) removed."

re: fclean all
