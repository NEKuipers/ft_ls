# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nkuipers <nkuipers@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/03/03 12:40:13 by nkuipers      #+#    #+#                  #
#    Updated: 2022/10/15 21:10:00 by nickkuipers   ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME			=	ft_ls
SRCS			=	main.c \
					parse_input.c \
					parse_utils.c \
					utils.c
CFILES      	=   $(SRCS:%=src/%)
OFILES      	=   $(CFILES:.c=.o)
CFLAGS          =   -Wall -Wextra -Werror
INCLUDES        =   -I includes -I lib/libft
LIBS            =   lib/libft/libft.a
# LIB LOCATIONS
LIBFT_LOC       =   lib/libft
# COLORS
WHITE   = \x1b[37;01m
CYAN    = \x1b[36;01m
PINK    = \x1b[35;01m
BLUE    = \x1b[34;01m
YELLOW  = \x1b[33;01m
GREEN   = \x1b[32;01m
RED     = \x1b[31;01m
BLACK   = \x1b[30;01m
RESET   = \x1b[0m

all: $(NAME)

$(NAME): $(OFILES)
	@echo "$(WHITE)/-----      Compiling libft     -----\\ $(RESET)"
	@make bonus -C $(LIBFT_LOC)
	@echo "$(WHITE)/-----      Creating ft_ls...\
	.    -----\\ $(RESET)"
	@gcc $(CFLAGS) $(INCLUDES) $(OFILES) $(LIBS) -o $(NAME)
	@echo "$(GREEN) Compiling complete. Name of executable is \
	'ft_ls'. $(RESET)"

%.o: %.c
	@echo "$(WHITE)Compiling: $<"
	@gcc $(INCLUDES) -o $@ -c $< $(CFLAGS)

clean:
	@echo "$(WHITE)/-----      Cleaning libft      -----\\ $(RESET)"
	@make fclean -C $(LIBFT_LOC)
	@echo "$(WHITE)/-----      Cleaning the rest     -----\\ $(RESET)"
	@echo "$(WHITE) Cleaning..."
	@rm -f $(OFILES) 

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
