/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 10:14:08 by maalexan          #+#    #+#             */
/*   Updated: 2023/07/09 20:29:15 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	assess_len(char *str, int len, char **copy)
{
	t_ctrl	*control;
	t_env	*variable;
	char	*src;
	char	temp;

	if (!str || !len)
		return (0);
	src = NULL;
	control = get_control();
	temp = str[len];
	str[len] = '\0';
	variable = search_var(str, control->env);
	if (variable)
		src = variable->value;
	str[len] = temp;
	if (copy && src)
		ft_memcpy(*copy, src, ft_strlen(src));
	if (src)
		return (ft_strlen(src));
	return (0);
}

static int	expand_var(char *line, int *i, char **copy)
{
	char	*start;
	int		len;

	(*i)++;
	start = &line[*i];
	len = 0;
	if (ft_isdigit(*start))
		len = 0;
	else if (*start == '?')
		len = 0; //change after implementing special var
	else
		while (ft_isalnum(line[*i]) || line[*i] == '_')
			(*i)++;
	if (&line[*i] == start)
		len = 0;
	else
	{
		len = assess_len(start, &line[*i] - start, copy);
		(*i)--;
	}
	return (len);
}

char	*copy_expansion(char *line, int len)
{
	char	*expanded;
	int		i;
	int		j;
	int		quoted;
	char	*temp;

	i = 0;
	j = 0;
	quoted = 0;
	expanded = malloc(sizeof(char) * len);
	if (!expanded)
		exit_program(OUT_OF_MEMORY);
	while (line[j])
	{
		if (line[j] == '\'')
			quoted = !quoted;
		if (!quoted && line[j] == '$')
		{
			temp = expanded + i;
			i += expand_var(line, &j, &temp) + 1;
		}
		expanded[i++] = line[j++];
	}
	expanded[i] = '\0';
	return (expanded);
}

char	*expanded_line(char *line)
{
	int		i;
	int		total_len;
	char	*test;

	i = 0;
	total_len = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			get_quote(line, &i);
		if (!line[i])
			break ;
		if (line[i] == '$')
			total_len += expand_var(line, &i, NULL);
		else
			total_len++;
		i++;
	}
	test = copy_expansion(line, total_len + 1);
	return (test);
}
