# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/01 15:45:53 by omghazi           #+#    #+#              #
#    Updated: 2024/09/13 13:01:01 by omghazi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			= $(addprefix src/, main.c signals.c \
                	  $(addprefix builtins/, cd.c echo.c env.c exit.c export.c export_utils.c pwd.c unset.c) \
                	  $(addprefix Parsing/, parse.c parse_utils.c parse_utils2.c env.c here_doc.c expansion.c expansion_utils.c) \
                	  $(addprefix utils/, safe_free.c execution_utils.c execution_utils2.c libft_pro_max.c store_execution.c store_node.c wildcard.c print.c) \
                	  $(addprefix Execution/, execution.c execution_process.c execve_pro_max.c find_path.c multi_cmds.c process.c red_process.c) \
                	  $(addprefix Lexer/, lexer.c lexer_utils.c lexer_utils2.c))
OBJS_DIR		= obj/
OBJS 			= $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
INCS_DIR		= includes/
INCS			= $(INCS_DIR)minishell.h $(INCS_DIR)types.h
LIBFT_DIR		= lib/libft/
LIBFT			= $(LIBFT_DIR)libft.a
CFLAGS			= -I$(INCS_DIR) -I$(LIBFT_DIR) 
CFLAGS			+= -Wall -Werror -Wextra -Wpedantic -g -fsanitize=address
NAME			= minishell
RM			= rm -rf
ERASE			= \033[2K\r
BLUE			= \033[34m
YELLOW			= \033[33m
GREEN			= \033[32m
END			= \033[0m
LDFLAGS			= -L/Users/omghazi/.brew/opt/readline/lib -lreadline -lhistory

all:			$(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	cc $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)
	printf "$(ERASE)$(GREEN)$@ made\n$(END)"

$(OBJS_DIR)%.o : %.c $(INCS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@	
	printf "$(ERASE)$(BLUE) > Compilation :$(END) $<"

$(LIBFT) :
	make -C $(LIBFT_DIR) && make clean -C $(LIBFT_DIR)

clean :
	printf "$(YELLOW)$(OBJS_DIR) removed$(END)\n"
	$(RM) $(OBJS_DIR)

fclean : clean
	printf "$(YELLOW)$(NAME) removed$(END)\n"
	printf "$(YELLOW)$(LIBFT) removed$(END)\n"
	make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re : fclean all

.PHONY : clean

.SILENT:
