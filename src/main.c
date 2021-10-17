/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 16:03:37 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/17 00:18:56 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"
#include "exec.h"
#include "errors.h"

t_minishell	g_mini;

static const char	*get_cmd(char *const *argv)
{
	size_t	i;

	i = 1;
	while (argv[i])
	{
		if (ft_strncmp(argv[i], "-c", 3) != 0)
			return (argv[i]);
		++i;
	}
	return (NULL);
}

static void	execute_cmd(const char *cmd)
{
	t_tokenizer	tok;
	t_list		*tokens;
	t_node		*cmds;

	if (!cmd)
	{
		pset_err(SHELL_NAME, "-c", C_FLAG_ARG_REQ, GENERIC_ERR);
		return ;
	}
	if (!*cmd)
		return ;
	init_tokenizer(&tok);
	tok.str = (char *)cmd;
	tokens = tokenize(&tok);
	cmds = parse(tokens);
	process_cmd(cmds);
	ft_lstclear(&tokens, ft_str_free);
	nodeclear(&cmds);
}

int	main(int argc, char **argv, char **env)
{
	minishell_init(env);
	if (argc > 1 && ft_strncmp(argv[1], "-c", 3) == 0)
		execute_cmd(get_cmd(argv));
	else if (argc > 1)
		pset_err(SHELL_NAME, argv[1], UNSUPPORTED_ARG_OPT, GENERIC_ERR);
	else
	{
		minishell_loop();
		ft_putendl_fd("exit", STDOUT_FILENO);
	}
	minishell_destroy();
	return ((int)g_mini.code);
}
