/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 18:22:53 by maalexan          #+#    #+#             */
/*   Updated: 2023/06/18 18:30:52 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_list(t_pipe *ptr)
{
	if (!ptr)
		return ;
	clear_list(ptr->next);
	free(ptr);
}

static void	handle_read_error(t_pipe **prev, t_pipe **new)
{
	if (*prev)
	{
		clear_list((*prev)->next);
		(*prev)->next = NULL;
	}
	else
	{
		clear_list(*new);
		*new = NULL;
	}
}

static int	count_content(t_pipe *pip)
{
	int	len;

	len = 0;
	while (pip)
	{
		if (pip->next)
			len += CHUNK;
		else
			len += ft_strlen(pip->parsed);
		pip = pip->next;
	}
	return (len);
}

char	*copy_content(t_pipe *pip)
{
	char	*str;
	char	*tmp;
	int		len;

	str = NULL;
	len = count_content(pip);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	tmp = str;
	while (pip)
	{
		tmp += ft_strlcpy(tmp, pip->parsed, ft_strlen(pip->parsed) + 1);
		pip = pip->next;
	}
	return (str);
}

t_pipe	*parse_fd(int fd, t_pipe *prev)
{
	int		len;
	t_pipe	*new;

	new = malloc(sizeof(t_pipe));
	if (!new)
		return (NULL);
	*new = (t_pipe){0};
	len = read(fd, new->parsed, CHUNK);
	if (len < 0)
		return (free(new), NULL);
	else if (len != CHUNK)
		return (new);
	if (prev)
		prev->next = new;
	new->next = parse_fd(fd, new);
	if (!new->next)
	{
		handle_read_error(&prev, &new);
		if (!new)
			return (NULL);
	}
	if (prev)
		return (prev->next);
	else
		return (new);
}
