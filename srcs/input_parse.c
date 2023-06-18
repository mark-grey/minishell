/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:39:29 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/18 15:54:37 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct		s_args
{
	char			*arg;
	struct s_args	*next;
}					t_args;

typedef struct		s_cli
{
	char			*command;
	s_args			*args;
	char			*director;
	struct s_cli	*next;
}					t_cli;

/* VERIFICA SE É QUOTE
 * Comportamento do bash quando não encontra fechamento do quote:
 * 	bash: unexpected EOF while looking for matching quote.
 * 	bash: syntax error: unexpected end of file
 */
int	ft_isquote(char c)
{
	return (c == "\"" || c == "\'");
}

/* PEGA O TRECHO ENTRE QUOTES
 * Enquanto a quote estiver aberta, o restante do código
 * não será interpretado, considerando como parte do
 * conteúdo quotado.
 */
void	get_quote(char *input, int *i)
{
	char	quote;

	quote = input[*i];
	*i++;
	while (input[*i] != quote && input[*i])
			*i++;
	if (!input[*i])
		exit(0); //não fechou a quote
}

/* PEGA O COMANDO 
 * Pega apenas um comando até encontrar algum redirecionador.
 * Elimina espaços antes e depois.
 * Retorna uma string.
 */
char	*get_command(char *input, int i)
{
	int		size;
	int		start;
	char	*cmd;

	while (ft_isblank(input[i]) && input[i])
		i++;
	start = i;
	while (!ft_isredirector(input[i]) && input[i])
	{
		if (ft_isquote(input[i]))
			get_quote(input, &i);
		i++;
	}
	i--;
	while (ft_isblank(input[i]) && i)
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

/* VERIFICA SE É CARACTERE DE REDIRECIONADOR
 */
int	ft_isredirector(char c)
{
	return (c == ">" || c == "<" || c == "|");
}

/* PEGA O REDIRECIONADOR
 * Os redirecionadores possíveis são:
 * >, >>, <, << e |.
 */
char	*get_redirector(char *input, int i)
{
	int		size;
	int		start;
	char	*red;

	while (ft_isblank(input[i]) && input[i])
		i++;
	if (!input[i])
		return (NULL);
	start = i;
	while (ft_isredirector(input[i]) && input[i])
		i++;
	size = i - start + 1;
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
		if (get_command(char *input, int i))
			break ;
		if (!get_redirector(char *input, int i))
			break ;
		i++;
	}
}

// ============================================== //
int	main(int ac, char **av)
{
	if (ac != 2)
		return (-1);
	input_parse(av[1]);
}
