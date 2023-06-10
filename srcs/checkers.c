/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 21:32:31 by maalexan          #+#    #+#             */
/*   Updated: 2023/06/09 21:03:05 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *str)
{
	if (!ft_strncmp(str, "cleiton\0", 8))
	{
		printf("teste\n");
		return (1);
	}
	if (!ft_strncmp(str, "exit\0", 5))
	{
		free(str);
		exit(0);
	}
	return (0);
}
