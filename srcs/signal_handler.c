/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 14:49:23 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/17 14:59:07 by maalexan         ###   ########.fr       */
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

void	set_signals(int reset)
{
	struct sigaction	s_act;

	s_act = (struct sigaction){0};
	if (reset)
		s_act.sa_handler = SIG_DFL;
	else
		s_act.sa_handler = &sig_handler;
	s_act.sa_flags = 0;
	sigemptyset(&s_act.sa_mask);
	if (sigaction(SIGINT, &s_act, NULL) < 0)
		perror("sigint");
	if (!reset)
		s_act.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &s_act, NULL) < 0)
		perror("sigquit");
}

/* MODO NÃO INTERATIVO
Usado quando o minishell está no modo não-interativo,
o que significa que não está aguardando a entrada do
usuário. Por exemplo, quando um comando está em execução
(ou seja, cat), o minishell não deve reagir a SIGINT e
SIGQUIT porque apenas o processo em execução (cat)
precisa reagir a esses sinais.
*/
