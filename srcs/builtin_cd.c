/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 21:10:09 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/08 22:19:11 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//change path to variable home
static void	change_to_home_path(t_env *env)
{
	t_env	*home;

	home = search_var("HOME", env);
	if (!home)
		return (perror("cd: HOME not set"));
	if (!chdir(home->value))
		return (perror("chdir error")); //não sei qual erro botar
}

//change path to path
static void	change_to_arg_path(char *path)
{
	if (!chdir(path))
		return (perror("cd: %s: No such file or directory", path));
}

void	b_cd(char **path, t_env *env)
{
	if (!env)
		return ;
	else if ((*path)[1])
		return (perror("cd: too many arguments"));
	else if (!(*path))
		change_to_home_path(env);
	else
		change_to_arg_path(*path);
}
