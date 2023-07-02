/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 20:57:15 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/02 17:34:13 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	b_echo(char **args, int fd)
{
	if (!args)
		return ;
	if (ft_strncmp(*args, "-n\0", 3))
	{
		while (*args)
			ft_putstr_fd(*args++, fd);
		ft_putstr_fd("\n", fd);
	}
	else
	{
		args++;
		while (*args)
			ft_putstr_fd(*args++, fd);
	}
}
