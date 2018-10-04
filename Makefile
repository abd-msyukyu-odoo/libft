# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/04 12:40:14 by dabeloos          #+#    #+#              #
#    Updated: 2018/10/04 15:52:45 by dabeloos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

C_FILES		= ft_memset.c \
			  ft_bzero.c \
			  ft_memcpy.c \
			  ft_memccpy.c

O_FILES		= $(C_FILES:.c=.o)

FLAGS		= -c -Wall -Wextra -Werror

$(NAME):
			gcc $(FLAGS) $(C_FILES)
			ar -rcs $(NAME) $(O_FILES)

all:		$(NAME)

clean:
			rm -f $(O_FILES)

fclean:		clean
			rm -f $(NAME)

re:			fclean all
