/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:08:04 by maalexan          #+#    #+#             */
/*   Updated: 2023/06/28 20:17:26 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Builds a complete filename for checking with the access function,
 * joining the path and exec so the access function can be called
 * regardless of the current directory
 */
static char	*get_full_path(char *path, char *cmd, int path_len, int cmd_len)
{
	char	*full;

	full = malloc(path_len + cmd_len + 2);
	if (!full)
		return (NULL);
	ft_memcpy(full, path, path_len);
	ft_memcpy(full + path_len + 1, cmd, cmd_len);
	full[path_len] = '/';
	full[path_len + cmd_len + 1] = '\0';
	return (full);
}

/*
 * Checks if the complete path is an executable
 */
static char	*check_exec(char *path, char *cmd, int path_len, int cmd_len)
{
	char	*str;

	str = NULL;
	str = get_full_path(path, cmd, path_len, cmd_len);
	if (access(str, X_OK))
	{
		free(str);
		str = NULL;
	}
	return (str);
}

/*
 * Searches the directory "path" for an executable named "cmd"
 */
static char	*find_exec(char *path, char *cmd)
{
	struct dirent	*files;
	DIR				*dir;
	char			*full_path;
	size_t			len;

	dir = opendir(path);
	if (!dir)
		return (NULL);
	full_path = NULL;
	files = readdir(dir);
	len = ft_strlen(cmd);
	while (len && files)
	{
		if (!ft_strncmp(cmd, files->d_name, len + 1))
			full_path = check_exec(path, cmd, ft_strlen(path), len);
		if (full_path)
			break ;
		files = readdir(dir);
	}
	closedir(dir);
	return (full_path);
}

/*
 * Loops through path variable to find executable file
 */
char	*parse_path(char *env_path, char *cmd)
{
	char	*token;
	char	*str;

	str = NULL;
	str = find_exec(".", cmd);
	if (str)
		return (str);
	token = ft_strtok(env_path, ":");
	while (token)
	{
		str = find_exec(token, cmd);
		if (str)
			return (str);
		token = ft_strtok(NULL, ":");
	}
	return (NULL);
}
