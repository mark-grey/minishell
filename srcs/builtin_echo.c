/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 20:57:15 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/10 18:56:21 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_args (char **args)
{
	while (*args)
	{
		printf("%s", *args++);
		if (*args)
			printf(" ");
	}
}

void	b_echo(char **args)
{
	if (!args)
		return ;
	if (ft_strncmp(*args, "-n\0", 3))
	{
		print_args(args);
		printf("\n");
	}
	else
	{
		args++;
		print_args(args);
	}
}
