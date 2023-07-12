/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:37:15 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/11 21:31:21 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt_user(const char *prompt, t_env *env_list)
{
	char	*line;
	t_cli	*cmds;
	t_ctrl	*ctrl;
	char	*path;
	char	*expanded;

	path = get_var_value("PATH", env_list);
	line = readline(prompt);
	if (!line)
		exit_program(127);
	expanded = NULL;
	if (!bar_input(line))
	{
		expanded = expand_line(line);
		cmds = parse_input(expanded, path);
		if (cmds)
			call_builtin(cmds->cmd, cmds->args, env_list);
		ctrl = get_control();
		if (ctrl->cli)
			clear_command_input(cmds);
		ctrl->cli = NULL;
		if (expanded)
			free(expanded);
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
