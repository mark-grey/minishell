/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 19:38:31 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/08 23:27:18 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_err(char quote, char red_curr, char red_next)
{
	ft_putstr_fd("minishell: ", 2);
	if (quote)
	{
		ft_putstr_fd("unable to find matching `", 2);
		write(2, &quote, 1);
	}
	else
	{
		ft_putstr_fd("syntax error near unexpected token '", 2);
		write (2, &red_curr, 1);
		if (red_curr == red_next && red_curr != '|')
			write (2, &red_curr, 1);
	}
	ft_putstr_fd("'\n", 2);
}

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
	if (quote)
		print_err(quote, 0, 0);
	return (quote != 0);
}

static int	evaluate_redirector(char red_curr, char red_next)
{
	if (red_curr == '|')
		return (0);
	if (is_redirector_char(red_next) && red_curr == red_next)
		return (1);
	return (0);
}

static int	bad_redirector(char *str, int *i)
{
	char	red;
	int		fail;

	red = *str++;
	fail = 0;
	(*i)++;
	if (!evaluate_redirector(red, *str))
		fail = 1;
	else if (*str == '<' || *str == '>')
	{
		(*i)++;
		str++;
		if (is_redirector_char(*str--))
			fail = 1;
	}
	str--;
	if (fail)
		print_err(0, red, *(str + 1));
	return (fail);
}

int	bar_input(char *input)
{
	int	i;

	i = 0;
	while (ft_isblank(input[i]))
		i++;
	if (!input || is_redirector(input) || is_redirector(&input[i]))
		return (-1);
	if (check_unclosed_quotes(input))
		return (1);
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
