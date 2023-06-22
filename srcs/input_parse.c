/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:39:29 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/22 19:28:53 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* SEPARAR COMANDO DOS ARGUMENTOS
 * Separa a primeira palavra que deverá ser o comando,
 * do restante que deverão ser os argumentos.
 * Esta função leva em consideração a possibilidade
 * de haver múltiplos espaços, cria novas cópias
 * para cada informação e libera a memória da
 * string completa.
 */
void	command_divider(char *cli, t_cli *newnode)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	newnode->command = get_command(cli, &start, &end);
	if (!newnode->command)
		newnode->args = cli;
	else
		newnode->args = get_args(cli, &start, &end);
}

/* CRIAR VARIÁVEL
 * Cria um novo node e coloca no final da lista.
 */
t_cli	*add_cli(t_cli *prev, char *command, char *director)
{
	t_cli	*newnode;

	newnode = malloc(sizeof(t_cli));
	if (!newnode)
		exit(1);
	*newnode = (t_cli){0};
	if (prev)
		prev->next = newnode;
	command_divider(command, newnode);
	newnode->director = director;
	return (newnode);
}

t_cli	*input_parse(char *input)
{
	t_cli	*command_line;
	t_cli	*prev;
	char	*command;
	char	*director;
	int		i;

	i = 0;
	command = get_cli(input, &i);
	if (!command)
		return (NULL);
	director = get_redirector(input, &i);
	command_line = add_cli(NULL, command, director);
	prev = command_line;
	while (input[i] && director)
	{
		command = get_cli(input, &i);
		if (!command)
			exit(-1); // FALTA ARGUMENTO APÓS O DIRECIONADOR
		director = get_redirector(input, &i);
		prev = add_cli(prev, command, director);
	}
	return (command_line);
}
