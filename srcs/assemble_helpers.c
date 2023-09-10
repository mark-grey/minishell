/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 14:50:25 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/07 21:16:21 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_here	*make_new_heredoc(t_here *head)
{
	t_here	*node;

	node = malloc(sizeof(t_here));
	if (!node)
	{
		free_heredocs(head, 'c');
		exit_program(OUT_OF_MEMORY);
	}
	*node = (t_here){0};
	return (node);
}

t_cli	*make_new_cli(t_here *head)
{
	t_cli	*node;

	node = malloc(sizeof(t_cli));
	if (!node)
	{
		free_heredocs(head, 'c');
		exit_program(OUT_OF_MEMORY);
	}
	*node = (t_cli){0};
	return (node);
}

static void	clear_node(t_cli *cli)
{
	if (cli->args)
		clear_pbox(cli->args);
	if (cli->fd[0] > 2)
		close(cli->fd[0]);
	if (cli->fd[1] > 2)
		close(cli->fd[1]);
	free(cli);
}

t_cli	*remove_cli(t_cli *cli)
{
	t_cli	*next;
	t_cli	*temp;

	if (!cli)
		return (NULL);
	temp = get_control()->commands;
	next = cli->next;
	while (temp && temp->next != cli)
		temp = temp->next;
	if (get_control()->commands == cli)
		get_control()->commands = next;
	else
		temp->next = next;
	clear_node(cli);
	return (next);
}

t_token	*discard_tokens(t_token *token)
{
	t_token	*stt;
	t_token	*end;

	if (!token)
		return (NULL);
	stt = token;
	end = token;
	while (stt && stt->prev && stt->prev->type != PIPE)
		stt = stt->prev;
	token = stt;
	while (end && end->type != PIPE)
		end = end->next;
	if (end)
		end = end->next;
	if (!stt->prev)
		get_control()->tokens = end;
	stt = stt->prev;
	while (token != end)
		token = remove_token(token);
	if (end)
		end->prev = stt;
	if (stt)
	{
		if (!stt->next)
			remove_token(stt);
		else
			stt->next = end;
	}
	return (end);
}
