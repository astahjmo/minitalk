# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: johmatos <johmatos@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/05 16:49:35 by johmatos          #+#    #+#              #
#    Updated: 2022/11/08 22:23:06 by johmatos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= server client
SOURCES		:= client.c server.c
VPATH		:= src
INCLUDE		:= include/
BUILDDIR	:= objs/
OBJS		:= $(addprefix $(BUILDDIR), $(SOURCES:.c=.o))
CFLAGS		:= -Wextra -Werror -Wall
CC			:= gcc

ifndef DEBUG
	CFLAGS += -g
endif

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft
	$(CC) $(CFLAGS) ./objs/$@.o -Llibft -lft -o $@

$(BUILDDIR)%.o: %.c
	test -d $(BUILDDIR) || mkdir $(BUILDDIR)
	$(CC) $(CFLAGS) -Llibft -lft -c $< -o $@

clean:
	make clean -C ./libft
	rm -rf $(BUILDDIR)
	
fclean: clean
	make fclean -C ./libft
	rm -rf $(NAME)

.phony: fclean all
