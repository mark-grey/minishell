/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 20:25:59 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/28 22:11:34 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	b_env(t_env *list)
{
	while (list)
	{
		printf("%s=%s\n", list->key, list->value);
		list = list->next;
	}
}
