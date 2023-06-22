/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_input_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:28:47 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/22 19:29:08 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cli_list(t_cli *list)
{
	if (!list)
		return ;
	printf("Command: %s \t//\t Args: %s \t//\t Director: %s\n", list->command, list->args, list->director);
	print_cli_list(list->next);
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (-1);
	t_cli	*command_line = input_parse(av[1]);
	print_cli_list(command_line);
}
