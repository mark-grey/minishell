/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 18:19:17 by maalexan          #+#    #+#             */
/*   Updated: 2023/06/10 20:54:45 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	path_parser(char *env_path)
{
	char	*str;

	str = ft_strtok(env_path, ":");
	while (str)
	{
		printf("%s\n",str);
		str = ft_strtok(NULL, ":");
	}

}

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
	(void)argc;
	(void)argv;
	char *path = findpath(envp);
	char *pcopy = malloc(ft_strlen(path + 5));
	ft_strlcpy(pcopy, path + 5, ft_strlen(path + 5));
	path_parser(pcopy);
	free(pcopy);
}
