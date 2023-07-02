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
				return (i);
			else
				count++;
		}
		if (is_quote(args[i]))
			get_quote(args, &i);
		i++;
	}
	return (count);
}

void	clear_ptr_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

static char	*set_arg(char *args, char **pointer)
{
	char		*str;
	int			len;
	int			start;
	static int	new_arg;

	start = new_arg;
	len = count_args(&args[start], 1);
	(void)pointer;
	new_arg += len + 1;
	if (!args[new_arg])
	{
		len++;
		new_arg = 0;
	}
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
	{
		clear_ptr_array(pointer);
		exit_program(OUT_OF_MEMORY);
	}
	ft_strlcpy(str, &args[start], len + 1);
	return (str);
}

char	**stringify_args(char *args)
{
	int		i;
	int		count;
	char	**pointers;

	i = 0;
	count = count_args(args, 0);
	pointers = malloc(sizeof(char *) * (count + 1));
	if (!pointers)
		exit_program(OUT_OF_MEMORY);
	while (i <= count)
		pointers[i++] = NULL;
	i = 0;
	while (i < count)
		pointers[i++] = set_arg(args, pointers);
	return (pointers);
}

int	main(int argc, char **argv)
{
	char	**ptrs;

	if (argc < 2)
		return (-1);
	ptrs = stringify_args(argv[1]);
	print_args(ptrs);
	clear_ptr_array(ptrs);
}

//	gcc -Wall -Werror -Wextra -I ./incl ./srcs/exec_maker.c ./srcs/builtin_caller.c ./srcs/cleaner.c ./srcs/env_parser.c ./srcs/env_utils.c ./srcs/exec_finder.c ./srcs/input_parser_gets.c ./srcs/input_parser.c ./srcs/input_utils.c  ./libs/libft/libft.a -o execs 