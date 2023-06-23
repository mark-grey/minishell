/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:39:29 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/22 21:15:07 by inwagner         ###   ########.fr       */
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
void	cmd_divider(char *cli, t_cli *newnode, char *path)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	newnode->cmd = get_cmd(cli, &start, &end, path);
	if (!newnode->cmd)
		newnode->args = cli;
	else
		newnode->args = get_args(cli, &start, &end);
}

/* CRIAR VARIÁVEL
 * Cria um novo node e coloca no final da lista.
 */
t_cli	*add_cli(t_cli *prev, char *cmd, char *director, char *path)
{
	t_cli	*newnode;

	newnode = malloc(sizeof(t_cli));
	if (!newnode)
		exit(1);
	*newnode = (t_cli){0};
	if (prev)
		prev->next = newnode;
	cmd_divider(cmd, newnode, path);
	newnode->director = director;
	return (newnode);
}

t_cli	*parse_input(char *input, char *path)
{
	t_cli	*cmd_line;
	t_cli	*prev;
	char	*cmd;
	char	*director;
	int		i;

	i = 0;
	cmd = get_cli(input, &i);
	if (!cmd)
		return (NULL);
	director = get_redirector(input, &i);
	cmd_line = add_cli(NULL, cmd, director, path);
	prev = cmd_line;
	while (input[i] && director)
	{
		cmd = get_cli(input, &i);
		if (!cmd)
			exit(-1); // FALTA ARGUMENTO APÓS O DIRECIONADOR
		director = get_redirector(input, &i);
		prev = add_cli(prev, cmd, director, path);
	}
	return (cmd_line);
}
