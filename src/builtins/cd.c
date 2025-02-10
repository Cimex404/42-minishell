/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 08:14:13 by jgraf             #+#    #+#             */
/*   Updated: 2025/02/10 08:50:00 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	This is the custom implementation of the cd command.
*	with cd you can change the current working directory by provinding either an absolute or relative path.
*	This minishell can also handle the - operator, which changes the working directory to the previous one,
*	by reading the OLDPWD variable. OLDPWD is constantly updated when cd is used.
*	When do path is provided, the function will default to the home directory.
*/

static int	check_path_access(char *path, t_input *tok)
{
	if (access(path, F_OK) != 0)
	{
		handle_error(INVALID_FILE, path, tok);
		return (0);
	}
	if (access(path, X_OK) != 0)
	{
		handle_error(PERMISSION_ERROR, path, tok);
		return (0);
	}
	return (1);
}

static void	update_pwd(t_input *tok)
{
	char	pwd[1024];

	if (getcwd(pwd, sizeof(pwd)) != NULL)
	{
		tok->env = export_variable_sep("OLDPWD", my_getenv(tok->env, "PWD"), *tok);
		tok->env = export_variable_sep("PWD", pwd, *tok);
		tok->last_status = 0;
	}
}

void	change_dir(t_input *tok, char *path)
{
	if (!check_path_access(path, tok))
		return ;
	if (chdir(path) != 0)
	{
		handle_error(EXEC_ERROR, path, tok);
		return ;
	}
	update_pwd(tok);
}
