/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 19:41:07 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/16 23:08:05 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"
#include "exec.h"
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

void	minishell_init(char *const *env)
{
	g_mini.env = ft_strarr_dup(env);
	g_mini.code = 0;
	g_mini.stdin_fd = dup(STDIN_FILENO);
	g_mini.stdout_fd = dup(STDOUT_FILENO);
	signal(SIGINT, newline);
	signal(SIGQUIT, SIG_IGN);
}

void	minishell_destroy(void)
{
	close(g_mini.stdin_fd);
	close(g_mini.stdout_fd);
	ft_strarr_free(g_mini.env);
	rl_clear_history();
}

static char	*get_line(char *line)
{
	char	*tmp;

	line = readline("\001"FT_BOLD FT_BRED"\002"SHELL_NAME"\001"FT_RST"\002% ");
	if (!line)
	{
		g_mini.code = 0;
		return (NULL);
	}
	tmp = ft_strtrim(line, WHITESPACE);
	free(line);
	line = tmp;
	if (*line)
		add_history(line);
	return (line);
}

static void	free_memory(t_list **tokens, t_node **cmds, char *line)
{
	ft_lstclear(tokens, ft_str_free);
	nodeclear(cmds);
	free(line);
}

void	minishell_loop(void)
{
	t_tokenizer	tok;
	t_list		*tokens;
	t_node		*cmds;

	while (true)
	{
		init_tokenizer(&tok);
		tok.str = get_line(tok.str);
		if (!tok.str)
			return ;
		if (!*tok.str)
		{
			free(tok.str);
			continue ;
		}
		tokens = tokenize(&tok);
		cmds = parse(tokens);
		process_cmd(cmds);
		free_memory(&tokens, &cmds, tok.str);
	}
}
