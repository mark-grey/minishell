/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_call.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 19:34:20 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/28 20:08:40 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	call_builtin(char *builtin)
{
	if (!ft_strncmp(builtin, "ping\0", 5))
		printf("pong\n");
	else if(!ft_strncmp(builtin, "cd\0", 3))
		printf("cd\n");
	else if(!ft_strncmp(builtin, "pwd\0", 4))
		printf("pwd\n");
	else if(!ft_strncmp(builtin, "echo\0", 5))
		printf("echo\n");
	else if(!ft_strncmp(builtin, "unset\0", 6))
		printf("unset\n");
	else if(!ft_strncmp(builtin, "export\0", 7))
		printf("export\n");
	else if(!ft_strncmp(builtin, "env\0", 4))
		printf("env\n");
	else if (!ft_strncmp(builtin, "exit\0", 5))
		exit_program(0);
}
