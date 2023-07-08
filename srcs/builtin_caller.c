/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_caller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 19:34:20 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/08 16:12:06 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	call_builtin(char *builtin, char **args, t_env *env)
{
	if (!ft_strncmp(builtin, "ping\0", 5))
		printf("pong\n");
	else if (!ft_strncmp(builtin, "cd\0", 3))
		printf("cd\n");
	else if (!ft_strncmp(builtin, "pwd\0", 4))
		b_pwd();
	else if (!ft_strncmp(builtin, "echo\0", 5))
		b_echo(args, 1);
	else if (!ft_strncmp(builtin, "unset\0", 6))
		printf("unset\n");
	else if (!ft_strncmp(builtin, "export\0", 7))
		b_export(env, args);
	else if (!ft_strncmp(builtin, "env\0", 4))
		b_env(env);
	else if (!ft_strncmp(builtin, "exit\0", 5))
		exit_program(0);
}
