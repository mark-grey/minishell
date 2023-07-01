/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_maker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 16:18:47 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/01 20:43:57 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_args(char **args)
{
	int	i;

	i = 1;
	while (*args)
		printf("%i: %s\n\n", i++, *args++);
}

int	count_args(char *args)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (args[i])
	{
		if (args[i] == ' ')
			count++;
		if (is_quote(args[i]))
		{
			get_quote(args, &i);
		printf("\nJust finished a quote, am at i %i and *args is %c\n", i, args[i]);
		}
		i++;
	}
	return (count);
}

char	**stringify_args(char *args)
{
	int		i;
	int		count;
	char	**pointers;

	i = 0;
	count = count_args(args);
	printf("I counted %i args\n", count);
	pointers = malloc(sizeof(char *) * (count + 1));
	if (!pointers)
		exit_program(OUT_OF_MEMORY);
	pointers[count] = NULL;
	while (i < count)
		set_arg(args[i], )
	free(pointers);
	return (NULL);
}

int	main(int argc, char **argv)
{
	if (argc < 2)
		return (-1);
	stringify_args(argv[1]);
	print_args(argv);
}

//	gcc -Wall -Werror -Wextra -I ./incl ./srcs/exec_maker.c ./srcs/builtin_caller.c ./srcs/cleaner.c ./srcs/env_parser.c ./srcs/env_utils.c ./srcs/exec_finder.c ./srcs/input_parser_gets.c ./srcs/input_parser.c ./srcs/input_utils.c  ./libs/libft/libft.a -o execs 