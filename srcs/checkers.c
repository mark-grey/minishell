/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 21:32:31 by maalexan          #+#    #+#             */
/*   Updated: 2023/06/11 13:51:32 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *str, t_env *env_list)
{
	if (!ft_strncmp(str, "ping\0", 5))
	{
		printf("pong\n");
		return (1);
	}
	if (!ft_strncmp(str, "exit\0", 5))
	{
		clear_var_list(env_list);
		free(str);
		exit(0);
	}
	if (!ft_strncmp(str, "env\0", 4))
	{
		print_var_list(env_list);
		return (1);
	}
	return (0);
}
