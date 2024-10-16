/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:18:45 by nlewicki          #+#    #+#             */
/*   Updated: 2024/09/19 11:23:38 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_new_env_var(const char *name, char *value, int i)
{
	char	*new_var;
	char	**envp;
	char	**new_envp;

	envp = *env_vars();
	new_var = NULL;
	new_envp = ft_realloc(envp, (i + 2) * sizeof(char *));
	if (!new_envp)
		return (1);
	if (value && *value)
	{
		new_var = create_new_var(new_var, name, value);
		if (!new_var)
			return (1);
	}
	else
	{
		new_var = create_new_var(new_var, name, "");
		if (!new_var)
			return (1);
	}
	new_envp[i] = new_var;
	new_envp[i + 1] = NULL;
	*env_vars() = new_envp;
	return (0);
}

char	*create_new_var(char *new_var, const char *name, char *value)
{
	size_t	len;

	len = ft_strlen(name) + ft_strlen(value) + 2;
	new_var = malloc(len);
	if (!new_var)
		return (NULL);
	ft_strcpy(new_var, name);
	if (value && *value)
	{
		ft_strlcat(new_var, "=", len);
		ft_strlcat(new_var, value, len);
	}
	return (new_var);
}

int	add_or_update_env(char *name, char *value)
{
	char	**envp;
	int		i;
	char	*new_var;

	envp = *env_vars();
	i = 0;
	new_var = NULL;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], name, ft_strlen(name)) == 0
			&& (envp[i][ft_strlen(name)] == '='
			|| envp[i][ft_strlen(name)] == '\0'))
		{
			new_var = create_new_var(NULL, name, value);
			if (!new_var)
				return (1);
			free(envp[i]);
			envp[i] = new_var;
			return (0);
		}
		i++;
	}
	return (add_new_env_var(name, value, i));
}

int	set_export_error(char *name, char *value)
{
	if (!is_valid_identifier(name))
	{
		ft_err("export: ", name, ": not a valid identifier\n");
		return (free(name), 1);
	}
	if (add_or_update_env(name, value) != 0)
	{
		ft_err("export: failed to set variable ", name, "\n");
		return (free(name), 1);
	}
	free(name);
	return (0);
}
