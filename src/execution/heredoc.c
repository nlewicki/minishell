/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:03:52 by mhummel           #+#    #+#             */
/*   Updated: 2024/10/28 16:17:16 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	setup_heredoc_delimiter(char **delimiter, bool *expand)
{
	size_t	len;
	char	*new_delim;

	*expand = true;
	len = ft_strlen(*delimiter);
	if (len > 1 && (*delimiter)[0] == '\'' && (*delimiter)[len - 1] == '\'')
	{
		*expand = false;
		new_delim = ft_strndup(*delimiter + 1, len - 2);
		*delimiter = new_delim;
		return (true);
	}
	return (false);
}

static int	process_heredoc_line(char *line, int pipe_fd, bool expand)
{
	char	*expanded_line;

	if (!expand)
	{
		ft_putendl_fd(line, pipe_fd);
		return (0);
	}
	expanded_line = expand_env_variables(line);
	if (!expanded_line)
		return (1);
	ft_putendl_fd(expanded_line, pipe_fd);
	free(expanded_line);
	return (0);
}

static int	read_heredoc_input(char *delimiter, int *pipe_fd, bool expand)
{
	char	*line;

	g_interrupt = 0;
	while (1)
	{
		line = readline("> ");
		if (!line || g_interrupt)
		{
			if (g_interrupt)
				return (1);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			return (0);
		}
		if (process_heredoc_line(line, pipe_fd[1], expand))
			return (free(line), 1);
		free(line);
	}
	return (0);
}

int	handle_heredoc(char *delimiter)
{
	int		pipe_fd[2];
	bool	expand;
	bool	free_delim;
	int		result;

	if (!delimiter)
		return (-1);
	free_delim = setup_heredoc_delimiter(&delimiter, &expand);
	if (pipe(pipe_fd) == -1)
		return (-1);
	ft_sigmode_heredoc();
	result = read_heredoc_input(delimiter, pipe_fd, expand);
	ft_sigmode_shell();
	if (free_delim)
		free(delimiter);
	if (result)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		if (g_interrupt)
			*exit_status() = 130;
		return (-1);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}
