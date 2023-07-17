/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 11:07:41 by maalexan          #+#    #+#             */
/*   Updated: 2023/07/17 14:58:00 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(char **args)
{
	int	count;

	count = 1;
	while (*++args)
		count++;
	return (count);
}

char	**wrap_args(char *exec, char **args)
{
	int		i;
	int		len;
	char	**wrapped;

	i = 1;
	if (args)
		len = count_args(args);
	else
		len = 0;
	wrapped = malloc(sizeof(char *) * (len + 2));
	if (!wrapped)
		exit_program(OUT_OF_MEMORY);
	wrapped[0] = exec;
	while (i < len + 1)
		wrapped[i++] = *args++;
	wrapped[i] = NULL;
	return (wrapped);
}

static void	run_fork(char *exec, char **args, t_env *env)
{
	char	**packed_env;
	char	**packed_args;

	packed_args = wrap_args(exec, args);
	packed_env = stringify_envp(env);
	set_signals(1);
	if (execve(exec, packed_args, packed_env) < 0)
	{
		printf("Failed to run program %s\n", exec);
		clear_ptr_array(packed_env);
		if (packed_args)
			free(packed_args);
		exit_program(-1);
	}
}

void	call_execve(char *exec, char **args, t_env *env)
{
	pid_t	forked;
	int		wstatus;

	wstatus = 0;
	if (!exec)
		return ;
	forked = fork();
	if (!forked)
		run_fork(exec, args, env);
	if (forked < 0)
		printf("Failed to create child process\n");
	else
	{
		waitpid(forked, &wstatus, 0);
		if (WIFEXITED(wstatus))
			wstatus = (WEXITSTATUS(wstatus));
	}
}
