/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:20:20 by jgraf             #+#    #+#             */
/*   Updated: 2025/02/10 08:28:15 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Allowed by the subject!
static volatile sig_atomic_t	g_sigint_received = 0;

/*	These functions are used to handle the signals recieved by the program.
*	They are used to handle the SIGINT signal, which is the signal recieved when the user
*	presses CTRL+C.
*	The global variable above is allowed by the subject, as it is accessable by all threads of the program.
*	All signals are handled by separate threads, with the global variable, we can ensure that the signal is
*	recieved correctly and the program can continue running.
*	The sig_sigint function is called when the SIGINT signal is recieved.
*	The prompt is given back to the user on a new line, and the line is cleared.
*/

void	sig_sigint(int sig)
{
	(void)sig;
	g_sigint_received = 1;
	rl_replace_line("", 0);
	ft_fprintf(STDERR_FILENO, "\n");
	if (waitpid(-1, NULL, WNOHANG) == 0)
		return ;
	rl_on_new_line();
	rl_redisplay();
}

bool	get_and_reset_sigint(void)
{
	int	was_received;

	was_received = g_sigint_received;
	g_sigint_received = 0;
	return (was_received);
}
