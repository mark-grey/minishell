/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:08:04 by maalexan          #+#    #+#             */
/*   Updated: 2023/06/10 21:17:11 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Builds a complete filename for checking with the access function,
	joining the path and exec so the access function can be called
	regardless of the current directory
*/
char	*get_full_path(char *path, char *command, int path_len, int command_len)
{
	char	*full;

	full = malloc(path_len + command_len + 2);
	if (!full)
		return (NULL);
	ft_memcpy(full, path, path_len);
	ft_memcpy(full + path_len + 1, command, command_len);
	full[path_len] = '/';
	full[path_len + command_len + 1] = '\0';
	return (full);
}

/*
	Checks if the complete path is an executable
*/
char	*check_requested_exec(char *path, char *command, int path_len, int command_len)
{
	char	*str;

	str = NULL;
	str = get_full_path(path, command, path_len, command_len);
	if (access(str, X_OK))
	{
		free(str);
		str = NULL;
	}
	return (str);
}

/*
	Searches the directory "path" for an executable named "command"
*/
char	*find_exec(char *path, char *command)
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
	len = ft_strlen(command);
	while (len && files)
	{
		if (!ft_strncmp(command, files->d_name, len + 1))
			full_path = check_requested_exec(path, command, ft_strlen(path), len);
		if (full_path)
			break ;
		files = readdir(dir);
	}
	closedir(dir);
	return (full_path);
}

/*
	Loops through path variable to find executable file
*/
char	*path_parser(char *env_path, char *command)
{
	char	*token;
	char	*str;

	token = ft_strtok(env_path, ":");
	str = NULL;
	while (token)
	{
		str = find_exec(token, command);
		if (str)
			return (str);
		token = ft_strtok(NULL, ":");
	}
	return (NULL);
}
