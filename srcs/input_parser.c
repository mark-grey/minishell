/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:39:29 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/28 22:14:27 by maalexan         ###   ########.fr       */
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

/* INSERE O COMANDO EXECUTAVEL
 * Caso exista um comando na estrutura e o mesmo
 * não seja um builtin, o caminho completo para seu
 * acesso será incluído à estrutura de controle
 */
static void	set_exec(t_cli *newnode)
{
	t_ctrl	*control;

	control = get_control();
	if (newnode->cmd && !is_builtin(newnode->cmd))
	{
		newnode->full_exec = control->exec_path;
		control->exec_path = NULL;
	}
}

/* CRIAR VARIÁVEL
 * Cria um novo node e coloca no final da lista.
 */
t_cli	*add_cli(t_cli *prev, char *cli, char *director, char *path)
{
	t_cli	*newnode;

	newnode = malloc(sizeof(t_cli));
	if (!newnode)
	{
		if (cli)
			free(cli);
		if (director)
			free(director);
		exit_program(OUT_OF_MEMORY);
	}
	*newnode = (t_cli){0};
	if (prev)
		prev->next = newnode;
	newnode->director = director;
	if (cli)
		cmd_divider(cli, newnode, path);
	set_exec(newnode);
	return (newnode);
}

t_cli	*parse_input(char *input, char *path)
{
	t_ctrl	*control;
	t_cli	*prev;
	char	*cli;
	char	*director;
	int		i;

	i = 0;
	cli = get_cli(input, &i);
	director = get_redirector(input, &i);
	if (!cli && !director)
		return (NULL);
	control = get_control();
	control->cli = add_cli(NULL, cli, director, path);
	prev = control->cli;
	while (input[i] && director)
	{
		cli = get_cli(input, &i);
		director = get_redirector(input, &i);
		prev = add_cli(prev, cli, director, path);
	}
	return (control->cli);
}
