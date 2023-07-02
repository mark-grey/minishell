/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:12:40 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/02 18:19:09 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	b_pwd(void)
{
	char	current_path[PATH_MAX];

	if (getcwd(current_path, sizeof(current_path)) == NULL)
		exit_program(-1);
	printf("%s", current_path);
}
