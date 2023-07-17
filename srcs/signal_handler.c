/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 14:49:23 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/17 16:32:25 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* MODO INTERATIVO

*/
static void sig_handler(int sig)
{
	if (sig != SIGINT)
		return ;
	write(1, "\n", 1);
	rl_on_new_line(); // Mover o cursor para uma nova linha
	rl_replace_line("", STDIN_FILENO); // Limpar a linha de entrada atual
	rl_redisplay(); // Redisplay o prompt
}

/* MODO NÃO INTERATIVO
Usado quando o minishell está no modo não-interativo,
o que significa que não está aguardando a entrada do
usuário. Por exemplo, quando um comando está em execução
(ou seja, cat), o minishell não deve reagir a SIGINT e
SIGQUIT porque apenas o processo em execução (cat)
precisa reagir a esses sinais.
*/

static void	non_interactive_mode(int sig)
{
	(void)sig;
	write (1, "\n", 1);
}

void	set_signals(int mode)
{
	if (mode == 0)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	if (mode == 1)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	if (mode == 2)
	{
		signal(SIGINT, non_interactive_mode);
		signal(SIGQUIT, non_interactive_mode);
	}
}

