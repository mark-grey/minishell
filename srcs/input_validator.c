/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 19:38:31 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/05 23:00:35 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	validate_args(char **args)
{
	int	i;

	while (*args)
	{
		i = -1;
		while ((*args)[++i])
			if (is_quote((*args)[i]) && get_quote((*args)[i], &i))
				exit_program(-1);
		args++;
	}
}

void	validate_redirector(char *director)
{
	if (director && !is_redirector(director))
		exit_program(-1);
}

void	validate_cli(t_cli cli)
{
	validate_redirector(cli->redirector);
	validate_args(cli->args);
}
