/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 20:57:15 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/02 13:05:02 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_arg(char **args, int fd)
{
	while (*args)
		ft_putstr(*args++, fd);
}

void	b_echo(char **args, int fd)
{
	if (!args)
		return ;
	if (ft_strncmp(*args, "-n\0", 3))
	{
		print_arg(**args, fd);
		write(fd, "\n", fd);
	}
	else
	{
		args++;
		print_arg(**args, fd);
	}
}
