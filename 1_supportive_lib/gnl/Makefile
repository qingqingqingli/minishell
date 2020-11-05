# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rbakker <rbakker@student.42.fr>              +#+                      #
#                                                    +#+                       #
#    Created: 2020/02/06 11:51:36 by rbakker       #+#    #+#                  #
#    Updated: 2020/09/08 16:24:40 by roybakker     ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =		libgnl.a

SOURCES	=	get_next_line.c get_next_line_utils.c
OBJECTS_S =	${SOURCES:%.c=%.o}

FLAGS =		-Wall -Wextra -Werror
COMPILE	=	gcc
LIB	=		ar rc

GREEN = \033[38;5;46m
WHITE = \033[38;5;15m
GREY = \033[38;5;8m
ORANGE= \033[38;5;202m
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

.PHONY: all bonus clean fclean re
