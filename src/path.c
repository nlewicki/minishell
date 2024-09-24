/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:45:17 by nlewicki          #+#    #+#             */
/*   Updated: 2024/09/24 09:42:53 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

#define MAX_PATH 1024

char	*search_path(const char *file)
{
	char	*path;
	char	*path_copy;
	char	*dir;
	char	full_path[MAX_PATH];
	char	**envp;

	path = NULL;
	envp = *env_vars();
	if (!envp)
		return (NULL);
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			path = *envp + 5;
			break ;
		}
		envp++;
	}
	if (!path)
		return (NULL);
	path_copy = ft_strdup(path);
	if (!path_copy)
		return (NULL);
	dir = ft_strtok(path_copy, ":");
	while (dir != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, file);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (ft_strdup(full_path));
		}
		dir = ft_strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

int	execute_external_command(char **args)
{
	char	*command_path;
	pid_t	pid;
	int		status;

	if (args[0][0] == '/' || args[0][0] == '.')
		command_path = args[0];
	else
		command_path = search_path(args[0]);
	if (!command_path)
		return (1);
	pid = fork();
	if (pid == 0)
	{
		execve(command_path, args, *env_vars());
		perror("execve");
		exit(1);
	}
	else if (pid < 0)
	{
		perror("fork");
		if (command_path != args[0])
			free(command_path);
		return (1);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (command_path != args[0])
			free(command_path);
		return (WEXITSTATUS(status));
	}
}
