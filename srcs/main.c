/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:37:15 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/28 22:09:45 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_args(char **args)
{
	int	i;
	static int	argun;

	i = 1;
	argun++;
	while (*args)
		printf("\nPRINTING ARGS\nchar ** number %i\n arg%i: %s\n", argun, i++, *args++);
}

static void	print_cmds()
{
	t_ctrl	*ctrl = get_control();
	t_cli	*temp;
	char	**args;

	if (ctrl)
		temp = ctrl->cli;
	else
		temp = NULL;
	int	i = 1;
	args = NULL;
	while (temp)
	{
		if (temp && temp->cmd)
			printf("Command %i: %s\n", i, temp->cmd);
		if (temp && temp->args)
			printf("Arg %i: %s\n", i, temp->args);
		if (temp && temp->director)
			printf("Dir %i: %s\n", i, temp->director);
		if (temp && temp->full_exec)
			printf("Exec: %i: %s\n", i, temp->full_exec);
		if (temp->args)
			args = stringify_args(temp->args);
		if (args)
		{
			print_args(args);
			clear_ptr_array(args);
		}
		args = NULL;
		i++;
		temp = temp->next;
		write(1, "\n", 1);
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
