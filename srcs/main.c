/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:37:15 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/17 14:54:03 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	apply_prompt(char *line, char *path)
{
	t_cli	*cmds;
	t_ctrl	*ctrl;
	char	*expanded;

	ctrl = get_control();
	expanded = expand_line(line);
	cmds = parse_input(expanded, path);
	if (cmds)
	{
		update_env(cmds->args, cmds->cmd, cmds->exec);
		call_builtin(cmds->cmd, cmds->args, ctrl->env);
		call_execve(cmds->exec, cmds->args, ctrl->env);
	}
	if (ctrl->cli)
		clear_command_input(cmds);
	ctrl->cli = NULL;
	if (expanded)
		free(expanded);
}

void	prompt_user(const char *prompt, t_env *env_list)
{
	char	*line;
	char	*path;

	path = get_var_value("PATH", env_list);
	line = readline(prompt);
	if (!line)
		exit_program(127);
	add_history(line);
	if (!bar_input(line))
		apply_prompt(line, path);
	free(line);
}

int	main(int argc, char **argv, char **env)
{
	t_ctrl	*control;

	(void)argc;
	control = get_control();
	control->env = parse_env(env);
	update_env(argv, NULL, NULL);
	set_signals(0);
	while (1)
		prompt_user("minishell:> ", control->env);
	exit_program(0);
}
