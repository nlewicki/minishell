/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:02:29 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/28 15:48:08 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_flag(char *argv[], int argc, int *i)
{
	int	j;

	while (*i < argc && argv[*i][0] == '-' && argv[*i][1] == 'n')
	{
		j = 1;
		while (argv[*i][j] == 'n')
			j++;
		if (argv[*i][j] != '\0')
			break ;
		(*i)++;
	}
	return (*i > 1);
}

int	ft_echo(char *argv[], int argc)
{
	int		i;
	bool	n_flag;

	if (argv[0][4] != '\0')
	{
		printf("%s", argv[0] + 5);
		if (argv[1] != NULL)
			printf(" ");
	}
	i = 1;
	n_flag = is_flag(argv, argc, &i);
	while (i < argc)
	{
		printf("%s", argv[i]);
		if (i + 1 < argc)
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
	return (0);
}
