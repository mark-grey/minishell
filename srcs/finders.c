/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:08:04 by maalexan          #+#    #+#             */
/*   Updated: 2023/06/10 16:21:38 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_type(char *path, char *exec, int path_len, int exec_len)
{
	char	*full;
	int		is_exec;

	is_exec = 0;
	full = malloc(path_len + exec_len + 2);
	if (!full)
		return (-1);
	ft_memcpy(full, path, path_len);
	ft_memcpy(full + path_len + 1, exec, exec_len);
	full[path_len] = '/';
	full[path_len + exec_len + 1] = '\0';
	printf("%s\n", full);
	if (!access(full, X_OK))
		is_exec = 1;
	free(full);
	return (is_exec);
}

int	find_exec(char *path, char *exec_name)
{
	struct dirent	*files;
	DIR				*dir;
	size_t			len;

	dir = opendir(path);
	if (!dir)
		return (-1);
	len = ft_strlen(exec_name);
	while (len)
	{
		files = readdir(dir);
		if (!files)
			break ;
		if (!ft_strncmp(exec_name, files->d_name, len + 1))
			if (check_type(path, exec_name, ft_strlen(path), len))
				printf("GOTCHA\n");
	}
	closedir(dir);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
		return (1);
	find_exec(argv[1], argv[2]);
}
