/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 19:38:31 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/08 22:15:40 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_unclosed_quotes(char *str)
{
	char	quote;

	quote = 0;
	while (*str)
	{
		if (is_quote(*str) && !quote)
			quote = *str;
		else if (*str == quote)
			quote = 0;
		str++;
	}
	return (quote != 0);
}

static void	print_err(char c, char b)
{
	ft_putstr_fd("Syntax error near unexpected token '", 2);
	write (2, &c, 1);
	if (c == b && c != '|')
		write (2, &c, 1);
	ft_putstr_fd("'\n", 2);
}

static int	bad_redirector(char *str, int *i)
{
	char	red;
	int		fail;

	red = *str++;
	fail = 0;
	(*i)++;
	if (*str == '|')
		fail = 1;
	else if (*str == '<' || *str == '>')
	{
		(*i)++;
		str++;
		if (is_redirector_char(*str))
			fail = 1;
	}
	if (fail)
		print_err(red, *(str - 1));
	return (fail);
}

int	bar_input(char *input)
{
	int	i;

	if (!input)
		return (-1);
	if (check_unclosed_quotes(input))
	{
		ft_putstr_fd("Unclosed quote\n", 2);
		return (1);
	}
	i = 0;
	while (input[i])
	{
		if (is_quote(input[i]))
			get_quote(input, &i);
		if (is_redirector_char(input[i]))
			if (bad_redirector(&input[i], &i))
				return (2);
		i++;
	}
	return (0);
}
