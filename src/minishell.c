/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 19:41:07 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/18 21:09:01 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"
#include "exec.h"
#include "signals.h"
#include "environment.h"
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

void	minishell_init(char *const *env)
{
	char	*str;

	g_mini.env = ft_strarr_dup(env);
	str = ft_getenv(ENV_USER);
	if (str)
		g_mini.user = ft_strdup(str);
	else
		g_mini.user = NULL;
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
	free(g_mini.user);
	rl_clear_history();
}

static char	*get_line(char *line)
{
	char	*tmp;
	char	*prompt;

	prompt = get_prompt();
	line = readline(prompt);
	free(prompt);
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
