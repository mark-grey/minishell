/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:39:29 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/21 20:50:19 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* VERIFICA SE É QUOTE
 * Comportamento do bash quando não encontra fechamento do quote:
 * 	bash: unexpected EOF while looking for matching quote.
 * 	bash: syntax error: unexpected end of file
 */
int	ft_isquote(char c)
{
	return (c == '\"' || c == '\'');
}

/* VERIFICA SE É CARACTERE DE REDIRECIONADOR
 */
int	ft_isredirector(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

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
char	*get_command(char *input, int *i)
{
	int		size;
	int		start;
	char	*cmd;

	while (ft_isblank(input[*i]) && input[*i])
		(*i)++;
	start = *i;
	while (!ft_isredirector(input[*i]) && input[*i])
	{
		if (ft_isquote(input[*i]))
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
	if (!input[*i] || !ft_isredirector(input[*i]))
		return (NULL);
	start = *i;
	while (ft_isredirector(input[*i]) && input[*i])
		(*i)++;
	size = *i - start + 1;
	red = malloc(sizeof(char) * size);
	if (!red)
		exit(1);
	ft_strlcpy(red, &input[start], size);
	return (red);
}

// ============================================== //

/* SEPARAR COMANDO DOS ARGUMENTOS
 * Separa a primeira palavra que deverá ser o comando,
 * do restante que deverão ser os argumentos.
 * Esta função leva em consideração a possibilidade
 * de haver múltiplos espaços, cria novas cópias
 * para cada informação e libera a memória da
 * string completa.
 */
void	command_divider(char *str, t_cli *newnode)
{
	int	start;
	int	end;
	int	len;

	start = 0;
	end = 0;
	while (!ft_isblank(str[end]) && str[end])
		end++;
	len = end - start + 1;
	newnode->command = malloc(sizeof(char) * len);
	ft_strlcpy(newnode->command, &str[start], len);
	while (ft_isblank(str[end]) && str[end])
		end++;
	if (str[end])
	{
		start = end;
		while (str[end])
			end++;
		len = end - start + 1;
		newnode->args = malloc(sizeof(char) * len);
		ft_strlcpy(newnode->args, &str[start], len);
	}
	free(str);
}

// ============================================== //

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
	command = get_command(input, &i);
	if (!command)
		return (NULL);
	director = get_redirector(input, &i);
	command_line = add_cli(NULL, command, director);
	prev = command_line;
	while (input[i] && director)
	{
		command = get_command(input, &i);
		if (!command)
			exit(-1); // FALTA ARGUMENTO APÓS O DIRECIONADOR
		director = get_redirector(input, &i);
		prev = add_cli(prev, command, director);
	}
	return (command_line);
}

// ============================================== //
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
