/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:37:15 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/09 19:59:58 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_args(char **args)
{
	int	i;

	i = 1;
	if (!args)
		return ;
	while (*args)
		printf("[%i]%s\t", i++, *args++);
}

static void	print_cli_list(t_cli *list)
{
	if (!list)
		return ;
	printf("Cmd: %s \t//\t", list->cmd);
	printf("Args: ");
	print_args(list->args);
	printf(" \t//\tDirector: %s\n", list->director);
	print_cli_list(list->next);
}

void	prompt_user(const char *prompt, t_env *env_list)
{
	char	*line;
	t_cli	*cmds;
	t_ctrl	*ctrl;
	char	*path;

	path = get_var_value("PATH", env_list);
	(void)path;
	line = readline(prompt);
	if (!line)
		exit_program(127);
	if (!bar_input(line))
	{
		//printf("Line: %s\n", line);
		cmds = parse_input(line, path);

		print_cli_list(cmds);
		call_builtin(cmds->cmd, cmds->args, env_list);

		ctrl = get_control();
		if (ctrl->cli)
			clear_command_input(cmds);
		ctrl->cli = NULL;
	}
	free(line);
}

int	main(int argc, char **argv, char **env)
{
	t_ctrl	*control;

	(void)argc;
	control = get_control();
	control->env = parse_env(env);
	update_env(argv, NULL);
	while (1)
		prompt_user("minishell:> ", control->env);
}
