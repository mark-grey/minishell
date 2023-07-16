/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 14:49:23 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/16 17:29:11 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* MODO INTERATIVO

*/
static void sigint_handler(int sig_int)
{
	(void)sig_int;
	write(1, "\n", 1);
	rl_on_new_line(); // Mover o cursor para uma nova linha
	rl_replace_line("", STDIN_FILENO); // Limpar a linha de entrada atual
	rl_redisplay(); // Redisplay o prompt
}

void	set_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

/* MODO NÃO INTERATIVO
Usado quando o minishell está no modo não-interativo,
o que significa que não está aguardando a entrada do
usuário. Por exemplo, quando um comando está em execução
(ou seja, cat), o minishell não deve reagir a SIGINT e
SIGQUIT porque apenas o processo em execução (cat)
precisa reagir a esses sinais.
*/
