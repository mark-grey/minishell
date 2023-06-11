/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 18:19:17 by maalexan          #+#    #+#             */
/*   Updated: 2023/06/10 21:20:52 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*path_parser(char *env_path, char *command);

static char	*findpath(char **env)
{
	while (*env)
	{
		if (!ft_strncmp(*env++, "PATH=", 5))
			return (*(env - 1));
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*retu = NULL;

	if (argc != 2)
		return (1);
	char *path = findpath(envp);
	char *pcopy = malloc(ft_strlen(path + 5));
	ft_strlcpy(pcopy, path + 5, ft_strlen(path + 5));
	retu = path_parser(pcopy, argv[1]);
	if (retu)
		printf("%s\n", retu);
	free(pcopy);
}

/*
gcc -Wall -Werror -Wextra -I ./incl/ test/pathfinder.c srcs/finders.c libs/libft/libft.a -o pathfinder

Usage: ./pathfinder <executable name>

Find_exec test
int	main(int argc, char **argv)
{
	char *str;

	if (argc != 3)
		return (1);
	str = find_exec(argv[1], argv[2]);
	if (str)
	{
		printf("%s\n", str);
		free(str);
	}
}
*/