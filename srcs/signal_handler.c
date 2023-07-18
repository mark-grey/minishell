/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 14:49:23 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/18 17:42:54 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* MODO INTERATIVO
**	rl_on_new_line: Move o cursor para uma nova linha
**	rl_replace_line: Limpa a linha de entrada atual
**	rl_redisplay: Reexibe o prompt
*/
static void	sig_handler(int sig)
{
	t_ctrl	*ctrl;

	if (sig != SIGINT)
		return ;
	ctrl = get_control();
	write(1, "\n", 1);
	ctrl->last_exit = 130;
	rl_on_new_line();
	rl_replace_line("", STDIN_FILENO);
	rl_redisplay();
}

/* MODO NÃO INTERATIVO
** Usado quando o minishell está no modo não-interativo,
** o que significa que não está aguardando a entrada do
** usuário. Por exemplo, quando um comando está em execução
** (ou seja, cat), o minishell não deve reagir a SIGINT e
** SIGQUIT porque apenas o processo em execução (cat)
** precisa reagir a esses sinais.
*/

static void	non_interactive_mode(int sig)
{
	t_ctrl	*ctrl;

	ctrl = get_control();
	if (sig == SIGINT)
		ctrl->last_exit = 130;
	write (1, "\n", 1);
}

void	set_signals(int mode)
{
	if (mode == ACTIVE)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	if (mode == INACTIVE)
	{
		signal(SIGINT, non_interactive_mode);
		signal(SIGQUIT, non_interactive_mode);
	}
	if (mode == DEFAULT)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}
