/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse_gets.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 22:24:30 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/21 22:27:26 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* PEGA O TRECHO ENTRE QUOTES
 * Enquanto a quote estiver aberta, o restante do código
 * não será interpretado, considerando como parte do
 * conteúdo quotado.
 */
void	get_quote(char *input, int *i)
{
	char	quote;

	quote = input[(*i)++];
	while (input[*i] != quote && input[*i])
			(*i)++;
	if (!input[*i])
		exit(0); //não fechou a quote
}

/* PEGA O COMANDO 
 * Pega apenas um comando até encontrar algum redirecionador.
 * Elimina espaços antes e depois.
 * Retorna uma string.
 */
char	*get_cli(char *input, int *i)
{
	int		size;
	int		start;
	char	*cmd;

	while (ft_isblank(input[*i]) && input[*i])
		(*i)++;
	start = *i;
	while (!is_redirector(input[*i]) && input[*i])
	{
		if (is_quote(input[*i]))
			get_quote(input, i);
		(*i)++;
	}
	(*i)--;
	while (ft_isblank(input[*i]) && *i)
		(*i)--;
	if (*i < start)
		return (NULL);
	size = ++(*i) - start + 1;
	cmd = malloc(sizeof(char) * size);
	if (!cmd)
		exit(1);
	ft_strlcpy(cmd, &input[start], size);
	return (cmd);
}

/* PEGA O REDIRECIONADOR
 * Os redirecionadores possíveis são:
 * >, >>, <, << e |.
 */
char	*get_redirector(char *input, int *i)
{
	int		size;
	int		start;
	char	*red;

	while (ft_isblank(input[*i]) && input[*i])
		(*i)++;
	if (!input[*i] || !is_redirector(input[*i]))
		return (NULL);
	start = *i;
	while (is_redirector(input[*i]) && input[*i])
		(*i)++;
	size = *i - start + 1;
	red = malloc(sizeof(char) * size);
	if (!red)
		exit(1);
	ft_strlcpy(red, &input[start], size);
	return (red);
}

char	*get_command(char *cli, int *start, int *end)
{
	int		len;
	char	*cmd;

	while (!ft_isblank(cli[*end]) && cli[*end])
		(*end)++;
	len = *end - *start + 1;
	cmd = malloc(sizeof(char) * len);
	if (!cmd)
		exit (0);
	ft_strlcpy(cmd, &cli[*start], len);
	if (!is_bt(cmd) && !is_ex(cmd))
	{
		*start = 0;
		free(cmd);
		return (NULL);
	}
	return (cmd);
}

char	*get_args(char *cli, int *start, int *end)
{
	int		len;
	char	*args;

	while (ft_isblank(cli[*end]) && cli[*end])
		(*end)++;
	if (cli[*end])
	{
		*start = *end;
		while (cli[*end])
			(*end)++;
		len = *end - *start + 1;
		args = malloc(sizeof(char) * len);
		ft_strlcpy(args, &cli[*start], len);
	}
	else
		args = NULL;
	free(cli);
	return (args);
}
