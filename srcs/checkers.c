/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 21:32:31 by maalexan          #+#    #+#             */
/*   Updated: 2023/06/13 20:59:42 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *builtin, t_env *env_list, char *args)
{
	(void)args;
	if (!ft_strncmp(builtin, "", 1))
		return (1);
	else if (!ft_strncmp(builtin, "env", 3))
		print_var_list(env_list);
	else if (!ft_strncmp(builtin, "echo", 5))
		printf("Soon: echo\n");
	else if (!ft_strncmp(builtin, "cd", 3))
		printf("Soon: cd\n");
	else if (!ft_strncmp(builtin, "pwd", 4))
		printf("Soon: pwd\n");
	else if (!ft_strncmp(builtin, "export", 3))
		printf("Soon: export\n");
	else if (!ft_strncmp(builtin, "unset", 3))
		printf("Soon: unset\n");
	else if (!ft_strncmp(builtin, "exit", 5))
	{
		clear_var_list(env_list);
		free(builtin);
		exit(0);
	}
	else if (!ft_strncmp(builtin, "ping", 5))
		printf("pong\n");
	else
		return (0);
	return (1);
}

int	is_exec(char *path, char *command)
{
	char	*exec_path;
	char	*temp_path;
	size_t	len;

	if (!path || !command)
		return (0);
	len = ft_strlen(path);
	temp_path = malloc(sizeof(char) * len + 1);
	if (!temp_path)
		return (0);
	ft_strlcpy(temp_path, path, len);
	exec_path = NULL;
	exec_path = path_parser(temp_path, command);
	free(temp_path);
	if (exec_path)
	{
		printf("%s\n", exec_path);
		free(exec_path);
		return (1);
	}
	return (0);
}
