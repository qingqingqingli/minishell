# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rbakker <marvin@codam.nl>                    +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/29 08:44:29 by rbakker       #+#    #+#                  #
#    Updated: 2020/11/08 16:57:38 by qli           ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SOURCES	= 	ft_printf.c scan_operations.c signed_integers.c characters.c \
			string.c percentage_sign.c hexa_lower.c hexa_upper.c pointers.c \
			unsigned_integers.c ft_printf_utils.c ft_printf_utils2.c

OBJECTS_S =	${SOURCES:%.c=%.o}

FLAGS =		-Wall -Wextra -Werror
COMPILE	=	gcc
LIB	=		ar rc

GREEN = \033[38;5;46m
WHITE = \033[38;5;15m
GREY = \033[38;5;8m
ORANGE = \033[38;5;202m
RED = \033[38;5;160m

all: $(NAME)

%.o: %.c
	@echo "$(GREY)Compiling...				$(WHITE)$<"
	@$(COMPILE) $(FLAGS) -c -o $@ $<

$(NAME): $(OBJECTS_S)
	@echo "$(ORANGE)Creating library..."
	@$(LIB) $(NAME) $(OBJECTS_S) $?
	@echo "$(GREEN)Succesful"

clean:
	@/bin/rm -f $(OBJECTS_S)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
