/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 11:07:41 by maalexan          #+#    #+#             */
/*   Updated: 2023/07/15 11:59:57 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	call_execve(char *exec, char **args, t_env *env)
{
	char	**packed_env;
	pid_t	forked;
	int		status;
	
	if (!exec)
		return ;
	forked = fork();
	if (!forked)
	{
		packed_env = stringify_envp(env);
		execve(exec, args, packed_env);
		printf("Failed to run program %s\n", exec);
		clear_ptr_array(packed_env);
		exit_program(-1);
	}
	if (forked < 0)
		printf("Failed to create child process\n");
	else
		waitpid(forked, &status, 0);
}

/* Below here is chatgpt suggestion on my take
void	call_execve(char *exec, char **args, t_env *env)
{
	char	**packed_env;
	pid_t	forked;
	int		status;
	
	if (!exec)
		return ;
	forked = fork();
	if (forked == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (forked == 0)
	{
		packed_env = stringify_envp(env);
		if (execve(exec, args, packed_env) == -1)
		{
			perror("execve");
			clear_ptr_array(packed_env);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (waitpid(forked, &status, 0) == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		else if (WIFEXITED(status))
			printf("My child finished with status %d\n", WEXITSTATUS(status));
	}
}
*/