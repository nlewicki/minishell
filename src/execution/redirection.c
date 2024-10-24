/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:16:29 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/24 11:12:05 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_redirection_error(char *filename, char *error_msg)
{
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error_msg, 2);
}

int	apply_single_redirection(char *symbol, char *filename)
{
	if (ft_strcmp(symbol, "<") == 0)
		return (redirect_input(filename));
	else if (ft_strcmp(symbol, ">") == 0)
		return (redirect_output(filename, 0));
	else if (ft_strcmp(symbol, ">>") == 0)
		return (redirect_output(filename, 1));
	return (0);
}

int	redirect_input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		print_redirection_error(file, "No such file or directory");
		return (*exit_status() = 1, 1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	redirect_output(char *file, int append)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags = flags | O_APPEND;
	else
		flags = flags | O_TRUNC;
	fd = open(file, flags, 0644);
	if (fd < 0)
	{
		ft_putstr_fd(file, 2);
		ft_putendl_fd(": Permission denied", 2);
		return (*exit_status() = 1, 1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	handle_redirections(t_list *command_list)
{
	t_list		*current;
	t_command	*cmd;
	int			orig_stdin;
	int			orig_stdout;

	orig_stdin = dup(STDIN_FILENO);
	orig_stdout = dup(STDOUT_FILENO);
	current = command_list;
	while (current)
	{
		cmd = (t_command *)current->content;
		if (apply_redirections(cmd))
		{
			restore_std_fds(orig_stdin, orig_stdout);
			return (1);
		}
		current = current->next;
	}
	close(orig_stdin);
	close(orig_stdout);
	return (0);
}
