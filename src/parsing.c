/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:23:02 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/03 09:13:34 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

typedef struct s_trim
{
	char	*result;
	size_t	i;
	size_t	j;
	size_t	len;
	bool	is_space;

}	t_trim;

void	handle_history(char *input)
{
	if (g_signal == 0)
	{
		if (ft_strlen(input) > 0)
			add_history(input);
		else
			free(input);
	}
}

bool	isspecials(char c)
{
	char	*specials;

	specials = "<>|\'\"$";
	while (*specials)
	{
		if (c == *specials)
			return (true);
		specials++;
	}
	return (false);
}

int	handle_operator(t_trim *trim, char *input)
{
	if (trim->j > 0 && !isspace(trim->result[trim->j - 1]))
		trim->result[trim->j++] = ' ';
	trim->result[trim->j++] = input[trim->i];
	if ((input[trim->i] == '<' && input[trim->i + 1] == '<')
		|| (input[trim->i] == '>' && input[trim->i + 1] == '>'))
		trim->result[trim->j++] = input[++trim->i];
	if (input[trim->i] != '$')
		trim->result[trim->j++] = ' ';
	return (0);
}

int	handle_quotes(t_trim *trim, char *input)
{
	char quote;

	if (trim->j > 0 && (!isspace(trim->result[trim->j - 1])))
		trim->result[trim->j++] = ' ';
	quote = input[trim->i];
	trim->result[trim->j++] = input[trim->i++];
	while ((input[trim->i] != '\0') && (input[trim->i] != quote))
		trim->result[trim->j++] = input[trim->i++];
	if (input[trim->i] == quote)
	{
		trim->result[trim->j++] = input[trim->i];
		trim->result[trim->j++] = ' ';
		return (0);
	}
	else
	{
		printf("Missing closing quote\n");
		return (1);
	}
}

int	handle_specials(t_trim *trim, char *input)
{
	char	tmp;
	int		ret;

	if ((input[trim->i] == '\'') || (input[trim->i] == '\"'))
	{
		ret = handle_quotes(trim, input);
		if (ret != 0)
			return (ret);
		trim->is_space = true;
	}
	else if (input[trim->i] == '|' || input[trim->i] == '>'
		|| input[trim->i] == '<' || input[trim->i] == '$')
	{
		tmp = input[trim->i];
		ret = handle_operator(trim, input);
		if (ret != 0)
			return (ret);
		if (tmp == '$')
			trim->is_space = false;
		else
			trim->is_space = true;
	}
	return (0);
}

int	trim_str(t_trim *trim, char *input)
{
	int	ret;

	trim->i = 0;
	trim->j = 0;
	trim->is_space = false;
	while (trim->i < trim->len)
	{
		if (isspecials(input[trim->i]))
			ret = handle_specials(trim, input);
			if (ret != 0)
				return (ret);
		else if (isspace(input[trim->i]))
		{
			if (!trim->is_space && trim->j > 0)
			{
				trim->result[trim->j++] = ' ';
				trim->is_space = true;
			}
		}
		else
		{
			trim->result[trim->j++] = input[trim->i];
			trim->is_space = false;
		}
		trim->i++;
	}
	trim->result[trim->j] = '\0';
	return (0);
}

char	*trim_whitespace(char *input)
{
	t_trim	trim;
	char	*new;
	int		ret;

	trim.len = ft_strlen(input);
	trim.result = ft_calloc(sizeof(char), trim.len + 100);
	if (!trim.result)
	{
		return (NULL);
	}
	ret = trim_str(&trim, input);
	if (ret != 0)
	{
		free(trim.result);
		return (NULL);
	}
	printf("result: %s\n", trim.result);
	new = ft_strtrim(trim.result, " \t\f\n\v\r");
	if (!new)
		return (NULL);
	printf("trimmed: %s\n", input);
	return (new);
}

int	parse_input(char *input)
{
	char	*new;
	char	**tokens;


	printf("input: %s\n", input);
	new = trim_whitespace(input);
	if (!new)
		return (1);


	tokens = split_space_quotes(new);
	free(new);
	if (!tokens)
		return (1);

	size_t	i;
	i = 0;
	while (tokens[i] != NULL)
	{
		printf("Token %zu:%s\n", i, tokens[i]);
		i++;
	}
	printf("total tokens: %zu\n", i);
	free_token_array(tokens);
	return (0);
}
