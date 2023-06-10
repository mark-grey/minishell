/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:37:15 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/10 14:30:47 by inwagner         ###   ########.fr       */
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

void	print_env(char **env)
{
	ft_putstr_fd("\nEnviromental variables:\n\n", 1);
	while (*env)
	{
		ft_putstr_fd(*env++, 1);
		write(1, "\n", 2);
	}
	write(1, "\n", 1);
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
