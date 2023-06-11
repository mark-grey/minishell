/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 21:32:31 by maalexan          #+#    #+#             */
/*   Updated: 2023/06/11 11:38:13 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Testing part
void	print_env(char **env)
{
	while (*env)
	{
		ft_putstr_fd(*env++, 1);
		write(1, "\n", 2);
	}
	write(1, "\n", 1);
}

void	print_var_list(t_env *list)
{
	while (list)
	{
		printf("%s=%s\n", list->key, list->value);
		list = list->next;
	}
}
// End test

int	is_builtin(char *str, t_env *env_list)
{
	if (!ft_strncmp(str, "ping\0", 5))
	{
		printf("pong\n");
		return (1);
	}
	if (!ft_strncmp(str, "exit\0", 5))
	{
		free(str);
		exit(0);
	}
	if (!ft_strncmp(str, "env\0", 4))
	{
		print_var_list(env_list);
		return (1);
	}
	return (0);
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
