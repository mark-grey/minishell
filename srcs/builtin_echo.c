/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 20:57:15 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/08 20:23:34 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	b_echo(char **args)
{
	if (!args)
		return ;
	if (ft_strncmp(*args, "-n\0", 3))
	{
		while (*args)
			printf("%s", *args++);
		printf("\n");
	}
	else
	{
		args++;
		while (*args)
			printf("%s", *args++);
	}
}
