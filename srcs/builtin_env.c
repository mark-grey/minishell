/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 20:25:59 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/17 19:51:21 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_env(char **path, t_env *list)
{
	t_env	*head;

	if (path)
		return (ft_putstr_fd("env: too many arguments\n", STDERR_FILENO), 1);
	head = list;
	list = list->next;
	while (list)
	{
		ft_putstr_fd(list->key, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putstr_fd(list->value, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		list = list->next;
	}
	ft_putstr_fd(head->key, STDOUT_FILENO);
	ft_putstr_fd("=", STDOUT_FILENO);
	ft_putstr_fd(head->value, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
