/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:37:15 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/11 14:10:27 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_program(int code, t_env *list)
{
	if (list)
		clear_var_list(list);
	exit(code);
}

void	prompt_user(const char *prompt, t_env *env_list)
{
	char	*line;
	char	*path;

	path = get_var_value("PATH", env_list);
	line = readline(prompt);
	if (!line)
		exit_program(127, env_list);
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
