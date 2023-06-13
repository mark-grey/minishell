/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_parse_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:01:31 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/10 15:29:47 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(char **env)
{
	while (*env)
	{
		ft_putstr_fd(*env++, 1);
		write(1, "\n", 2);
	}
	write(1, "\n", 1);
}

void	print_var_list(t_env *list)
{
	while (list)
	{
		printf("%s=%s\n", list->key, list->value);
		list = list->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_env	*env_list;

	(void)argc;
	(void)argv;
	print_env(env);
	env_list = parse_env(env);
	print_var_list(env_list);
	(void)env_list;
}
