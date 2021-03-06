# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/20 14:41:19 by vsporer           #+#    #+#              #
#    Updated: 2017/10/23 12:51:12 by vsporer          ###   ########.fr        #
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
C_TOOLS =			\033[1;33;44m

PATH_LIBFT =		libft/
PATH_SRC =			src/
PATH_INPUT =		$(PATH_SRC)input/
PATH_BUILTINS =		$(PATH_SRC)builtins/
PATH_TOOLS =		$(PATH_SRC)tools/
PATH_OBJ =			objs/

CC =				gcc -Wall -Werror -Wextra
INC =				-I includes/ -I libft/includes/

SRC =				$(PATH_SRC)main.c\
					$(PATH_SRC)get_env.c\
					$(PATH_SRC)msh_switch.c\
					$(PATH_SRC)msh_signal.c\
					$(PATH_SRC)signal_handler.c\
					$(PATH_SRC)msh_error.c

INPUT =				$(PATH_INPUT)wait_cmd.c\
					$(PATH_INPUT)edit_line.c\
					$(PATH_INPUT)event_manager.c\
					$(PATH_INPUT)line_to_tab.c\
					$(PATH_INPUT)list.c\
					$(PATH_INPUT)add_dlist.c\
					$(PATH_INPUT)prev_cmd.c\
					$(PATH_INPUT)clean_line.c\
					$(PATH_INPUT)set_term_param.c

BUILTINS =			$(PATH_BUILTINS)msh_exit.c\
					$(PATH_BUILTINS)msh_cd.c\
					$(PATH_BUILTINS)msh_echo.c\
					$(PATH_BUILTINS)msh_env.c\
					$(PATH_BUILTINS)msh_setenv.c\
					$(PATH_BUILTINS)msh_unsetenv.c\
					$(PATH_BUILTINS)msh_exec.c

TOOLS =				$(PATH_TOOLS)count_var.c\
					$(PATH_TOOLS)search_var.c\
					$(PATH_TOOLS)msh_tablen.c\
					$(PATH_TOOLS)exit_value.c\
					$(PATH_TOOLS)del_cmdtab.c\
					$(PATH_TOOLS)del_env.c\
					$(PATH_TOOLS)last_pid.c\
					$(PATH_TOOLS)save_cmdline.c\
					$(PATH_TOOLS)signal_value.c\
					$(PATH_TOOLS)check_directory.c\
					$(PATH_TOOLS)new_cmd_line.c\
					$(PATH_TOOLS)check_escape.c\
					$(PATH_TOOLS)add_one_str.c\
					$(PATH_TOOLS)get_cursor_pos.c\
					$(PATH_TOOLS)check_father.c\
					$(PATH_TOOLS)next_cmdline.c

OBJ =				$(patsubst $(PATH_SRC)%.c, $(PATH_OBJ)%.o, $(SRC))\
					$(patsubst $(PATH_INPUT)%.c, $(PATH_OBJ)%.o, $(INPUT))\
					$(patsubst $(PATH_TOOLS)%.c, $(PATH_OBJ)%.o, $(TOOLS))\
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

$(PATH_OBJ)%.o: $(PATH_TOOLS)%.c
	@echo "$(C_TOOLS)Compiling $< to $@$(C_RESET)"
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
