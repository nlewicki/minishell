/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_len.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:22:47 by mhummel           #+#    #+#             */
/*   Updated: 2024/10/24 17:27:21 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_whitespace(t_trim *trim_info, char *str)
{
	trim_info->len++;
	while (str[trim_info->i] != '\0' && ft_isspace(str[trim_info->i]))
		trim_info->i++;
}

static void	handle_quotes_len(t_trim *trim_info, char *str)
{
	char	quote_char;

	quote_char = str[trim_info->i];
	trim_info->i++;
	trim_info->len++;
	while (str[trim_info->i] != quote_char && str[trim_info->i] != '\0')
	{
		trim_info->i++;
		trim_info->len++;
	}
	if (str[trim_info->i] == quote_char)
	{
		trim_info->i++;
		trim_info->len++;
	}
}

static void	handle_special_char(t_trim *trim_info, char *str)
{
	if (trim_info->i > 0 && !ft_isspace(str[trim_info->i - 1])
		&& !is_special_char(str[trim_info->i - 1]))
		trim_info->len++;
	trim_info->len++;
	if (str[trim_info->i + 1] != '\0' && !ft_isspace(str[trim_info->i + 1]))
		trim_info->len++;
	trim_info->i++;
}

static void	handle_double_redirection(t_trim *trim_info, char *str)
{
	if (trim_info->i > 0 && !ft_isspace(str[trim_info->i - 1])
		&& !is_special_char(str[trim_info->i - 1]))
		trim_info->len++;
	trim_info->len += 2;
	if (str[trim_info->i + 2] != '\0' && !ft_isspace(str[trim_info->i + 2]))
		trim_info->len++;
	trim_info->i += 2;
}

int	ft_trim_len(char *input)
{
	t_trim	trim_info;

	trim_info.i = 0;
	trim_info.len = 0;
	while (input[trim_info.i] != '\0')
	{
		if (ft_isspace(input[trim_info.i]))
			handle_whitespace(&trim_info, input);
		else if (input[trim_info.i] == '\'' || input[trim_info.i] == '\"')
			handle_quotes_len(&trim_info, input);
		else if ((input[trim_info.i] == '<' && input[trim_info.i + 1] == '<')
			|| (input[trim_info.i] == '>' && input[trim_info.i + 1] == '>'))
			handle_double_redirection(&trim_info, input);
		else if (is_special_char(input[trim_info.i]))
			handle_special_char(&trim_info, input);
		else
		{
			trim_info.len++;
			trim_info.i++;
		}
	}
	return (trim_info.len);
}
