/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 07:44:32 by jgraf             #+#    #+#             */
/*   Updated: 2025/02/10 08:39:26 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	The main function first installs the signal handlers.
*	It takes the allocated copy of the environment variables.
*	Then the main loop is entered. The loop reads the input, creates tokens out of it,
*	checks if the input is valid, executes it if so.
*	Then, the tokens are freed and the loop starts again.
*	When the EOF signal (CTRL+D) is recieved, the loop breaks and the program exits.
*	When the command line is empty, the loop directly jumps to the next iteration.
*/

static void	minishell(char **env_copy, t_input *tokens)
{
	char	*prompt;

	while (true)
	{
		prompt = readline(TEAL "MINISHELL❯ " RESET);
		if (prompt == NULL)
			break ;
		else
		{
			if (get_and_reset_sigint())
				tokens->last_status = 130;
			if (prompt[0] == '\0')
			{
				free(prompt);
				continue ;
			}
			*tokens = create_tokens(prompt, env_copy, tokens->last_status);
			add_history(prompt);
			free(prompt);
			if (validate_input(tokens) == 0)
				execute_input(tokens);
			free_tokens(&tokens->tokens, tokens->token_count - 1);
			env_copy = tokens->env;
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_input	tokens;
	char	**env_copy;

	(void)ac, (void)av;
	signal(SIGINT, sig_sigint);
	signal(SIGQUIT, SIG_IGN);
	env_copy = init_env(env);
	tokens.last_status = 0;
	minishell(env_copy, &tokens);
	free_env(tokens.env);
	return (tokens.last_status);
}
