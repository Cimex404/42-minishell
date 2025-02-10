/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_prechanges.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:03:14 by nmonzon           #+#    #+#             */
/*   Updated: 2025/02/10 08:16:00 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	These function are used to replace the SHLVL variable with the correct
*	value at the start of the program.
*/

char	**add_envvar_pre(char **env, char *name, char *con)
{
	char	**env_new;
	int		i;

	env_new = malloc(sizeof(char *) * (get_entry_number(env) + 2));
	i = 0;
	while (env[i] != NULL)
	{
		env_new[i] = ft_strdup(env[i]);
		i ++;
	}
	env_new[i] = malloc(ft_strlen(name) + ft_strlen(con) + 2);
	create_and_add_new(env_new[i], name, con);
	env_new[i + 1] = NULL;
	return (env_new);
}

char	**replace_envvar_pre(char **env, char *name, char *con)
{
	int		i;
	char	*replacement;

	i = 0;
	while (ft_strncmp(env[i], name, ft_strlen(name)) != 0
		&& env[i] != NULL)
		i ++;
	replacement = malloc(ft_strlen(name) + ft_strlen(con) + 2);
	env[i] = replace_and_add_new(replacement, name, con, env[i]);
	return (env);
}
