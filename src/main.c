/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:20:30 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/23 13:49:11 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_input(char *input)
{
	t_list	*tokens;
	t_list	*tabel;
	t_list	*new_tabel;

	handle_history(input);
	tokens = parse_input(input);
	if (tokens == NULL)
		return ;
	tabel = create_tabel(tokens);
	new_tabel = expansion(tabel);
	execution(new_tabel);
	ft_lstclear(&tokens, free_token);
	ft_lstclear(&tabel, free_tabel);
}

void	main_loop(void)
{
	char	*input;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break ;
		if (input[0] != '\0')
			process_input(input);
		free(input);
	}
	printf("exit\n");
}

void	check_l(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **envp)
{
	// atexit(check_l);
	(void)argc;
	(void)argv;
	if (*env_vars() == NULL)
		*env_vars() = copy_envp(envp);
	if (!env_vars())
		return (perror("Failed to copy envp"), 1);
	*exit_status() = 0;
	*is_expanded() = 0;
	handle_shlvl();
	handle_signals();
	main_loop();
}
