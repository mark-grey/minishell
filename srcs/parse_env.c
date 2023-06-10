/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 09:34:50 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/10 14:31:47 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* PARSE ENV
 * Distribui cada uma das variáveis de env em uma lista linkada.
 */
t_env	*parse_env(char **env)
{
	t_env	*env_list;
	t_env	*prev_env;

	env_list = ft_add_var(NULL, *env++);
	prev_env = env_list;
	while (*env)
	{
		prev_env = ft_add_var(prev_env, *env);
		env++;
	}
	return (env_list);
}
