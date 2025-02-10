/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:00:54 by jgraf             #+#    #+#             */
/*   Updated: 2025/02/10 08:12:43 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	This is the custom implementation of the pwd command.
*	pwd is used to print the current working directory.
*/

void	print_working_dir(t_input *tok)
{
	char	pwd[1024];

	if (getcwd(pwd, sizeof(pwd)) != NULL)
		printf("%s\n", pwd);
	tok->last_status = 0;
}
