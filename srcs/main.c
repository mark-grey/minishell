/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:37:15 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/11 11:45:04 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_value(char *value, t_env *env_list)
{
	char	*list_value;
	t_env	*env_node;

	list_value = NULL;
	env_node = NULL;
	env_node = ft_search_var_node(value, env_list);
	if (env_node)
		list_value = env_node->value;
	return (list_value);
}

void	prompt_user(const char *prompt, t_env *env_list)
{
	char	*line;
	char	*path;

	path = get_var_value("PATH", env_list);
	line = readline(prompt);
	if (!line)
		exit(127);
	if (!is_builtin(line, env_list))
		if (!is_exec(path, line))
			printf("Command \"%s\" not found\n", line);
	free(line);
}

int	main(int argc, char **argv, char **env)
{
	t_env	*env_list;

	(void)argc;
	(void)argv;
	env_list = parse_env(env);
	while (1)
		prompt_user("minishell:> ", env_list);
}
