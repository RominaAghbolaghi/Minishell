# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/20 15:02:24 by mpeulet           #+#    #+#              #
#    Updated: 2023/12/07 14:24:04 by mpeulet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= 	main.c $(addprefix parsing/, dollar3.c verif_quotes_utils.c structure2_2.c syntax_error_utils.c verif_quote.c enum.c enum_utils.c structure.c syntax_error.c env.c dollar_quote.c dollar_quote2.c dollar.c dollar2.c structure2.c)\
			$(addprefix pipex/, builtin.c pipex.c pipex_utils.c here_doc.c here_doc_utils.c free.c parsing.c redirect_fd.c here_doc2.c)\
			$(addprefix builtin/, echo.c exit_builtin.c env_builtin.c export.c export_noargs.c pwd.c cd.c cd2.c ft_printf_fd.c unset.c unset_utils.c utils2.c utils.c signals.c )\
			$(addprefix extra/, main_utils.c free_data.c)

OBJS	=	${SRCS:.c=.o}

LIBFT	= libft/libft.a

NAME	= minishell

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g3

VMINI	= valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes\
					 --suppressions=/mnt/nfs/homes/mpeulet/test/minishell_final/minishell.supp \
					 --track-fds=yes

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:		${NAME}

$(NAME):	${OBJS}
			make -C libft
			$(CC) $(OBJS) $(LIBFT) -g -o $(NAME) -lreadline

clean:
				make -C libft clean
				rm -f ${OBJS}

fclean:		clean
				make clean
				rm -f ${NAME} $ $(LIBFT)

re:				fclean all

rlleaks:		$(NAME)
					$(VMINI) ./minishell

.PHONY:			all clean fclean re rlleaks
