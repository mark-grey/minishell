/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:37:15 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/27 21:33:57 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_cmds()
{
	t_ctrl *ctrl = get_control();
	t_cli	*temp;

	if (ctrl)
		temp = ctrl->cli;
	else
		temp = NULL;
	int	i = 1;
	while (temp)
	{
		if (temp && temp->cmd)
			printf("Command %i: %s\n", i, temp->cmd);
		if (temp && temp->args)
			printf("Arg %i: %s\n", i, temp->args);
		if (temp && temp->director)
			printf("Dir %i: %s\n", i, temp->director);
		i++;
		temp = temp->next;
	}
}

void	prompt_user(const char *prompt, t_env *env_list)
{
	char	*line;
	t_cli	*cmds;
	t_ctrl	*ctrl;
	char	*path;

	path = get_var_value("PATH", env_list);
	line = readline(prompt);
	if (!line)
		exit_program(127);
	cmds = parse_input(line, path);
	print_cmds();
	ctrl = get_control();
	if (ctrl->cli)
		clear_command_input(cmds);
	ctrl->cli = NULL;
	free(line);
}

int	main(int argc, char **argv, char **env)
{
	t_ctrl	*control;

	(void)argc;
	(void)argv;
	control = get_control();
	control->env = parse_env(env);
	while (1)
		prompt_user("minishell:> ", control->env);
}
