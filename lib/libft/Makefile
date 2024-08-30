# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/14 00:47:15 by omghazi           #+#    #+#              #
#    Updated: 2024/08/26 16:03:01 by omghazi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_memset.c		\
		ft_bzero.c		\
		ft_memcpy.c		\
		ft_memcpy.c	\
		ft_memmove.c 	\
		ft_memchr.c		\
		ft_strlen.c		\
		ft_isalpha.c 	\
		ft_isdigit.c	\
		ft_isalnum.c	\
		ft_isascii.c	\
		ft_isprint.c	\
		ft_toupper.c	\
		ft_tolower.c	\
		ft_strchr.c		\
		ft_strrchr.c	\
		ft_strncmp.c	\
		ft_strlcpy.c	\
		ft_strlcat.c	\
		ft_atoi.c		\
		ft_memcmp.c		\
		ft_strnstr.c	\
		ft_strdup.c		\
		ft_calloc.c		\
		ft_substr.c		\
		ft_strjoin.c	\
		ft_strtrim.c	\
		ft_split.c		\
		ft_itoa.c		\
		ft_strmapi.c		\
		ft_striteri.c		\
		ft_putchar_fd.c		\
		ft_putstr_fd.c		\
		ft_putnbr_fd.c		\
		ft_putendl_fd.c		\
		mr_propre.c	\
		create_leaks_list.c	\

SBONUS = ft_lstnew_bonus.c		\
	 	 ft_lstadd_front_bonus.c	\
		 ft_lstsize_bonus.c		\
		 ft_lstlast_bonus.c		\
		 ft_lstadd_back_bonus.c	\
		 ft_lstdelone_bonus.c		\
		 ft_lstclear_bonus.c		\
		 ft_lstiter_bonus.c		\
		 ft_lstmap_bonus.c

NAME = libft.a
CC = cc
CFLAGS = -Wextra -Werror -Wall
RM = rm -f
OBJS = $(SRC:.c=.o)
BOBJS = $(SBONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		ar cr $(NAME) $(OBJS)

%.o: %.c libft.h
		$(CC) $(CFLAGS) -c $< -o $@

bonus: $(BOBJS)
		ar cr $(NAME) $(BOBJS)

clean:
		$(RM) $(OBJS) $(BOBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: clean
