/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:38:52 by jgraf             #+#    #+#             */
/*   Updated: 2025/02/10 08:06:13 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	This is the custom implementation of the echo command.
*	echo is used to print the provided arguments to the standard output.
*	You can use the -n flag to not print a newline at the end of the output.
*/

static void	print_tokens(t_input tok, int start_idx)
{
	int	i;

	i = start_idx;
	while (i < tok.token_count)
	{
		if (tok.tokens[i].token)
		{
			printf("%s", tok.tokens[i].token);
			if (i < tok.token_count - 1 && tok.tokens[i + 1].type == STRING)
				printf(" ");
			else
				break ;
		}
		i ++;
	}
}

void	builtin_echo(t_input *tok, int no_nl, int start_idx)
{
	if (tok->token_count == 1)
	{
		if (!no_nl)
			printf("\n");
		tok->last_status = 0;
		return ;
	}
	print_tokens(*tok, start_idx);
	if (!no_nl)
		printf("\n");
	tok->last_status = 0;
}
