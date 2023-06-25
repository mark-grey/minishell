/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_stringify.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 20:38:33 by maalexan          #+#    #+#             */
/*   Updated: 2023/06/22 20:39:07 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*copy_to_env(char *key, char *value)
{
	char	*new_var;
	int		key_len;
	int		val_len;

	key_len = ft_strlen(key) + 1;
	val_len = ft_strlen(value) + 1;
	new_var = malloc(sizeof(char) * (key_len + val_len));
	if (!new_var)
		return (NULL);
	ft_strlcpy(new_var, key, key_len);
	ft_strlcpy(new_var + key_len, value, val_len);
	new_var[key_len - 1] = '=';
	return (new_var);
}

char	**stringify_envp(t_env *list)
{
	char	**env;
	int		i;
	int		len;

	i = 0;
	len = count_list(list);
	env = malloc(sizeof(char *) * (len + 1));
	if (!env)
		return (NULL);
	while (i < len)
	{
		env[i] = copy_to_env(list->key, list->value);
		if (!env[i++])
			return (NULL);
		list = list->next;
	}
	env[i] = NULL;
	return (env);
}
