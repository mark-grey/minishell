/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 10:14:08 by maalexan          #+#    #+#             */
/*   Updated: 2023/07/11 17:31:22 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	assess_len(char *str, int len, char **copy)
{
	t_ctrl	*control;
	t_env	*variable;
	char	*src;
	char	temp;

	if (!*str || !len)
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
	len = 1;
	if (ft_isdigit(*start))
		(*i)++;
	else if (*start == '?')
		(*i)++; //change after implementing special var
	else
		while (ft_isalnum(line[*i]) || line[*i] == '_')
			(*i)++;
	len = assess_len(start, &line[*i] - start, copy);
	return (len);
}

int		valid_var_name(char c)
{
	return (c == '?' || ft_isalnum(c) || c == '_');
}

char	*copy_expansion(char *line, int len)
{
	char	*expanded;
	int		i;
	int		quoted;
	char	*cursor;

	i = 0;
	quoted = 0;
	expanded = malloc(sizeof(char) * len);
	if (!expanded)
		exit_program(OUT_OF_MEMORY);
	cursor = expanded;
	while (line[i])
	{
		if (line[i] == '\'')
			quoted = !quoted;
		if (!quoted && line[i] == '$' && valid_var_name(line[i + 1]))
			cursor += expand_var(line, &i, &cursor);
		if (line[i])
			*cursor++ = line[i++];
	}
	*cursor = '\0';
	return (expanded);
}

char	*expand_line(char *line)
{
	int		i;
	int		total_len;

	i = 0;
	total_len = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			total_len += get_quote(line, &i);
		if (line[i] == '$' && valid_var_name(line[i + 1]))
			total_len += expand_var(line, &i, NULL);
		if (line[i])//removed the else here
		{
			total_len++;
			i++;
		}
	}
	if (total_len)
		return (copy_expansion(line, total_len + 1));
	return (NULL);
}


//lol $-putz '$PATH' "PATH" $PATH "$PATH" "$a" s$_$PATH $