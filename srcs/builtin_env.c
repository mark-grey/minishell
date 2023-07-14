/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 20:25:59 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/12 20:51:55 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_env(t_env *list)
{
	t_env	*head;

	head = list;
	list = list->next;
	while (list)
	{
		printf("%s=%s\n", list->key, list->value);
		list = list->next;
	}
	printf("%s=%s\n", head->key, head->value);
	return (0);
}
