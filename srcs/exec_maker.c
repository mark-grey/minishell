/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_maker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 16:18:47 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/02 15:40:21 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_args(char **args)
{
	int	i;
printf("\ngonna print now:\n");
	i = 1;
	while (*args)
		printf("%i: %s\n\n", i++, *args++);
}

static int	count_args(char *args, int single_arg)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (args[i] == ' ' || !args[i + 1])
		{
			if (single_arg)
				{printf("I'm gonna leave at index args[%i], char: %i\n", i, (int)args[i]);return (i);}
			else
				count++;
		}
		if (is_quote(args[i]))
		{
			get_quote(args, &i);
		printf("\nJust finished a quote, am at i %i and *args is %c\n", i, args[i]);
		}
		i++;
	}
	return (count);
}

static char	*set_arg(char *args, char **pointer)
{
	int			len;
	static int	new_arg;

	printf("gonna count from %s\n", &args[new_arg]);
	len = count_args(&args[new_arg], 1);
	(void)pointer;
	new_arg += len + 1;
	if (!args[new_arg])
	{
		len++;
		new_arg = 0;
	}
	printf("len is %i\n", len);
	return NULL;
}

char	**stringify_args(char *args)
{
	int		i;
	int		count;
	char	**pointers;

	i = 0;
	count = count_args(args, 0);
	printf("\n\nI counted %i args\n", count);
	pointers = malloc(sizeof(char *) * (count + 1));
	if (!pointers)
		exit_program(OUT_OF_MEMORY);
	pointers[count] = NULL;
	while (i < count)
		pointers[i++] = set_arg(args, pointers);
	free(pointers);
	return NULL;
}

int	main(int argc, char **argv)
{
	if (argc < 2)
		return (-1);
	stringify_args(argv[1]);
	if (argv[2])
		stringify_args(argv[2]);
	print_args(argv + 1);
}

//	gcc -Wall -Werror -Wextra -I ./incl ./srcs/exec_maker.c ./srcs/builtin_caller.c ./srcs/cleaner.c ./srcs/env_parser.c ./srcs/env_utils.c ./srcs/exec_finder.c ./srcs/input_parser_gets.c ./srcs/input_parser.c ./srcs/input_utils.c  ./libs/libft/libft.a -o execs 