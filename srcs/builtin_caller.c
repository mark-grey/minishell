/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_caller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 19:34:20 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/11 20:06:31 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	call_builtin(char *builtin, char **args, t_env *env)
{
	if (!builtin)
		return ;
	if (!ft_strncmp(builtin, "ping", 5))
		printf("pong\n");
	else if (!ft_strncmp(builtin, "cd", 3))
		b_cd(args, env);
	else if (!ft_strncmp(builtin, "pwd", 4))
		b_pwd();
	else if (!ft_strncmp(builtin, "echo", 5))
		b_echo(args);
	else if (!ft_strncmp(builtin, "unset", 6))
		b_unset(env, args);
	else if (!ft_strncmp(builtin, "export", 7))
		b_export(env, args);
	else if (!ft_strncmp(builtin, "env", 4))
		b_env(env);
	else if (!ft_strncmp(builtin, "exit", 5))
		exit_program(0);
}
