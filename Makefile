# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/20 14:41:19 by vsporer           #+#    #+#              #
#    Updated: 2017/10/03 00:51:18 by vsporer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 				minishell
LIBFT =				libft/libft.a

C_RESET =			\033[0m
C_OK =				\033[32m
C_DEL =				\033[31m
C_SRC =				\033[44m
C_INPUT =			\033[36;44m
C_BUILTINS =		\033[32;44m

PATH_LIBFT =		libft/
PATH_SRC =			src/
PATH_INPUT =		$(PATH_SRC)input/
PATH_BUILTINS =		$(PATH_SRC)builtins/
PATH_OBJ =			objs/

CC =				gcc -Wall -Werror -Wextra
INC =				-I includes/ -I libft/includes/

SRC =				$(PATH_SRC)main.c\
					$(PATH_SRC)get_env.c\
					$(PATH_SRC)search_var.c\
					$(PATH_SRC)msh_switch.c\
					$(PATH_SRC)msh_error.c

INPUT =				$(PATH_INPUT)wait_cmd.c\
					$(PATH_INPUT)edit_line.c\
					$(PATH_INPUT)event_manager.c\
					$(PATH_INPUT)line_to_tab.c\
					$(PATH_INPUT)list.c\
					$(PATH_INPUT)prev_cmd.c\
					$(PATH_INPUT)clean_line.c\
					$(PATH_INPUT)set_term_param.c\
					$(PATH_INPUT)tools.c

BUILTINS =			$(PATH_BUILTINS)msh_exit.c

OBJ =				$(patsubst $(PATH_SRC)%.c, $(PATH_OBJ)%.o, $(SRC))\
					$(patsubst $(PATH_INPUT)%.c, $(PATH_OBJ)%.o, $(INPUT))\
					$(patsubst $(PATH_BUILTINS)%.c, $(PATH_OBJ)%.o, $(BUILTINS))

.PHONY: all clean fclean libft

all: libft $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@echo "Compiling $@ ..."
	@$(CC) $(INC) $^ -o $@
	@echo "$(C_OK)Done !$(C_RESET)"

$(LIBFT): libft

libft:
	@cd $(PATH_LIBFT) && $(MAKE)

$(PATH_OBJ)%.o: $(PATH_SRC)%.c
	@echo "$(C_SRC)Compiling $< to $@$(C_RESET)"
	@mkdir -p $(@D)
	@$(CC) $(INC) -c $< -o $@

$(PATH_OBJ)%.o: $(PATH_INPUT)%.c
	@echo "$(C_INPUT)Compiling $< to $@$(C_RESET)"
	@mkdir -p $(@D)
	@$(CC) $(INC) -c $< -o $@

$(PATH_OBJ)%.o: $(PATH_BUILTINS)%.c
	@echo "$(C_BUILTINS)Compiling $< to $@$(C_RESET)"
	@mkdir -p $(@D)
	@$(CC) $(INC) -c $< -o $@

clean:
	@rm -rf $(PATH_OBJ)
	@cd $(PATH_LIBFT) && $(MAKE) clean
	@echo "$(C_DEL)Object files removed.$(C_RESET)"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)
	@echo "$(C_DEL)$(NAME) and $(LIBFT) removed.$(C_RESET)"

test: all
	@echo "\\ \\ \\ \\ \\ \\BEGIN TEST/ / / / / /"
	@echo ""
	@./minishell
	@echo ""
	@echo "/ / / / / / END TEST \\ \\ \\ \\ \\ \\"

re: fclean all
