/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 19:38:31 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/09 19:18:38 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error(char *msg, char *ref)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(ref, 2);
	ft_putstr_fd("'\n", 2);
}

static int	check_unclosed_quotes(char *input, int *i)
{
	char	quote;

	quote = input[*i];
	get_quote(input, i);
	if (input[*i])
		return (0);
	print_error("unable to find matching `", &quote);
	return (-1);
}

static int	validate_pipe(char *input, int *i)
{
	int	j;

	j = *i;
	if (j)
		j--;
	while (ft_isblank(input[j]) && j)
		j--;
	if (!is_pipe(input[j]) && !ft_isblank(input[j]))
		return (0);
	print_error("unable to find matching `", "|");
	return (-1);
}

static int	validate_brackets(char *input, int *i)
{
	char	c;

	c = input[(*i)];
	(*i)++;
	if (input[*i] != c || !input[*i])
		return (0);
	(*i)++;
	while (ft_isblank(input[*i]))
		(*i)++;
	if (!(is_pipe(input[*i]) || is_bracket(input[*i]) || !input[*i]))
		return (0);
	c = input[*i];
	if (!c)
		print_error("syntax error near unexpected token `", "newline");
	else if (is_pipe(c) || is_bracket(c))
		print_error("syntax error near unexpected token `", &c);
	return (-1);
}

int	bar_input(char *input)
{
	int	i;

	if (!input)
		return (0);
	i = -1;
	while (input[++i])
	{
		if (is_quote(input[i]))
			if (check_unclosed_quotes(input, &i))
				return (-1);
		if (input[i] && is_pipe(input[i]))
			if (validate_pipe(input, &i))
				return (-1);
		if (input[i] && is_bracket(input[i]))
			if (validate_brackets(input, &i))
				return (-1);
	}
	return (0);
}
