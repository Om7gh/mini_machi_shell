SRCS			= $(shell find *.c)
OBJS 			= $(SRCS:.c=.o)
CFLAGS			= -Wall -Wextra -Werror
ARC				= ar rc
NAME			= libft.a
ERASE		:=	\033[2K\r
BLUE		:=	\033[34m
YELLOW		:=	\033[33m
GREEN		:=	\033[32m
END		:=	\033[0m

all:			$(NAME)

$(NAME):		$(OBJS)
	@$(ARC) $(NAME) $(OBJS)
	printf "$(ERASE)$(GREEN)$@ made\n$(END)"


%.o 			: %.c libft.h
	@$(CC) $(CFLAGS) -o $@ -c $<
	printf "$(ERASE)$(BLUE) > Compilation :$(END) $<"

clean:
	@$(RM) $(OBJS)

fclean:			clean
	printf "$(YELLOW)$(NAME) removed$(END)\n"
	@$(RM) $(NAME)
				
re:	fclean all
.SILENT: