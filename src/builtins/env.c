/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:16:35 by jgraf             #+#    #+#             */
/*   Updated: 2025/02/10 08:09:36 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	This is the custom implementation of the env command.
*	env is used to print the environment variables.
*/

char	*my_getenv(char **env, char *name)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], name, ft_strlen(name)) == 0
			&& env[i][ft_strlen(name)] == '=')
			return (env[i] + ft_strlen(name) + 1);
		i ++;
	}
	return (NULL);
}

int	my_getenv_index(char **env, char *name)
{
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], name, ft_strlen(name)) == 0
			&& env[i][ft_strlen(name)] == '=')
			return (i);
		i ++;
	}
	return (-1);
}

void	print_envs(t_input *tok)
{
	int		i;
	char	*equals_pos;

	i = 0;
	while (tok->env[i] != NULL)
	{
		equals_pos = ft_strchr(tok->env[i], '=');
		if (equals_pos && *(equals_pos + 1) != '\0')
			printf("%s\n", tok->env[i]);
		i++;
	}
	tok->last_status = 0;
}

/*	These functions are used for the standalone export command.
*	When export is used without any arguments, it will print the environment variables in alphabetical order.
*	It will also print variables that have no value, while the env command will not.
*/

static void	sort_envs(char **env)
{
	int		len;
	int		i;
	int		j;
	char	*tmp;

	len = 0;
	while (env[len])
		len++;
	i = -1;
	while (++i < len - 1)
	{
		j = -1;
		while (++j < len - i - 1)
		{
			if (ft_strcmp(env[j], env[j + 1]) > 0)
			{
				tmp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = tmp;
			}
		}
	}
}

void	print_sorted_env(char **env)
{
	int		i;
	char	*equals_pos;

	sort_envs(env);
	i = -1;
	while (env[++i])
	{
		equals_pos = ft_strchr(env[i], '=');
		if (equals_pos)
		{
			*equals_pos = '\0';
			if (*(equals_pos + 1) != '\0')
				printf("%s=\"%s\"\n", env[i], equals_pos + 1);
			else
				printf("%s\n", env[i]);
			*equals_pos = '=';
		}
		else
			printf("%s\n", env[i]);
	}
}
