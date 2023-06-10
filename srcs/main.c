/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:37:15 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/10 15:02:13 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt_user(const char *prompt)
{
	char	*line;

	line = readline(prompt);
	if (!line)
		exit(127);
	if (!is_builtin(line))
		printf("temp\n");
	free(line);
}

int	main(int argc, char **argv, char **env)
{
	t_env	*env_list;

	(void)argc;
	(void)argv;
	env_list = parse_env(env);
	(void)env_list;
	while (1)
		prompt_user("minishell:> ");
}
