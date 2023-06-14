/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:39:29 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/14 20:19:04 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_cli
{
	char			*command;
	char			*args;
	char			*director;
	struct s_cli	*next;
}					t_cli;

int	ft_isredirector(char c)
{
	return (c == ">" || c == "<" || c == "|");
}

/* VERIFICA SE É QUOTE
 * Comportamento do bash quando não encontra fechamento do quote:
 * 	bash: unexpected EOF while looking for matching `"'
 * 	bash: syntax error: unexpected end of file
 */
int	ft_isquote(char c)
{
	return (c == "\"" || c == "\'");
}

void	cu_ote(char *input, int *i)
{
	char	quote;

	quote = input[*i];
	*i++;
	while (input[*i] != quote && input[*i])
			*i++;
	if (!input[*i])
		exit(0); //não fechou a quote
}

/* DIVIDE EM COMANDOS
 * Pega apenas um comando até encontrar algum redirecionador.
 * Elimina espaços antes e depois.
 * Retorna uma string.
 */
char	*get_command(char *input, int i)
{
	int		size;
	int		start;
	char	*cmd;

	while (ft_isspace(input[i]) && input[i])
		i++;
	start = i;
	while (!ft_isredirector(input[i]) && input[i])
	{
		if (ft_isquote(input[i]))
			cu_ote(input, &i);
		i++;
	}
	i--;
	while (ft_isspace(input[i]) && i)
		i--;
	if (i <= start)
		return (NULL);
	size = ++i - start + 1;
	cmd = malloc(sizeof(char) * size);
	if (!cmd)
		exit(1);
	ft_strlcpy(cmd, input[start], size);
	return (cmd);
}

char	*get_redirector(char *input, int i)
{
	int		size;
	char	*red;

	while (ft_isspace(input[i]) && input[i])
		i++;
	size = i;
	while (ft_isredirector(input[i]) && input[i])
		i++;
	size = i - size + 1;
	red = malloc(sizeof(char) * size);
	if (!red)
		exit(1);
	ft_strlcpy(red, src, size);
	return (red);
}

char	*input_parse(char *input)
{
	char	**cmdbox;
	int		i;
	int		j;

	//Fazer lista linkada pra adicionar cada novo comando
	i = 0;
	j = 0;
	while (input[i])
	{
		get_command(char *input, int i)
		i++;
	}
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (-1);
	input_parse(av[1]);
}
