/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:38:18 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/17 10:38:51 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_shlvl(void)
{
	char	*shlvl_str;
	int		shlvl;
	char	*value;

	shlvl_str = get_our_env("SHLVL");
	if (!shlvl_str)
		shlvl = 0;
	else
		shlvl = atoi(shlvl_str);
	shlvl += 1;
	value = ft_itoa(shlvl);
	add_or_update_env("SHLVL", value);
	free(value);
}