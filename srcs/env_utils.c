/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 13:50:16 by maalexan          #+#    #+#             */
/*   Updated: 2023/06/11 13:53:01 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_var_list(t_env *list)
{
	if (!list)
		return ;
	printf("%s=%s\n", list->key, list->value);
	print_var_list(list->next);
}

void	clear_var_list(t_env *list)
{
	if (!list)
		return ;
	clear_var_list(list->next);
	if (list->key)
		free(list->key);
	free(list);
}
