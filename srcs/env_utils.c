/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 13:50:16 by maalexan          #+#    #+#             */
/*   Updated: 2023/06/22 21:01:34 by inwagner         ###   ########.fr       */
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

char	*get_var_value(char *value, t_env *env_list)
{
	char	*list_value;
	t_env	*env_node;

	list_value = NULL;
	env_node = NULL;
	env_node = search_var(value, env_list);
	if (env_node)
		list_value = env_node->value;
	return (list_value);
}
