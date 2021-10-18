/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 00:29:29 by laube             #+#    #+#             */
/*   Updated: 2021/10/18 19:44:25 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "parse.h"
#include "minishell.h"
#include "exec.h"
#include "errors.h"
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

static void	dispatch_cmd(t_node *node)
{
	if (ft_strncmp(node->argv[0], "echo", 5) == 0)
		ft_echo(node);
	else if (ft_strncmp(node->argv[0], "pwd", 4) == 0)
		ft_pwd(node);
	else if (ft_strncmp(node->argv[0], "cd", 3) == 0)
		ft_cd(node);
	else if (ft_strncmp(node->argv[0], "env", 4) == 0)
		ft_env(node);
	else if (ft_strncmp(node->argv[0], "unset", 6) == 0)
		ft_unset(node);
	else if (ft_strncmp(node->argv[0], "export", 7) == 0)
		ft_export(node);
	else if (ft_strncmp(node->argv[0], "exit", 5) == 0)
		ft_exit(node);
	else
		ft_cmd(node);
}

static void	execute(t_node *node)
{
	if (!op_control(node))
		return ;
	interpolate_arr(node->argv);
	interpolate_redirs(node->redirs);
	if (node->argv[0])
		dispatch_cmd(node);
}

static void	execute_subshell(t_node *node)
{
	pid_t	pid;
	int		wstatus;

	if (!op_control(node))
		return ;
	pid = fork();
	if (pid == -1)
	{
		pset_err(SHELL_NAME, NULL, strerror(errno), GENERIC_ERR);
		return ;
	}
	if (pid == 0)
	{
		execute(node);
		exit((int)g_mini.code);
	}
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		g_mini.code = WEXITSTATUS(wstatus);
}

static bool	process_heredocs(t_node *cmds)
{
	while (cmds)
	{
		if (!exec_heredocs(cmds->redirs, cmds->fd[0]))
			return (true);
		cmds = cmds->next;
	}
	return (false);
}

void	process_cmd(t_node *cmds)
{
	t_node	*start;
	bool	error;

	start = cmds;
	init_pipes(start);
	error = process_heredocs(cmds);
	while (!error && cmds)
	{
		if (!cmds->next)
			execute(cmds);
		else
			execute_subshell(cmds);
		fd_reset();
		cmds = cmds->next;
	}
	close_pipes(start);
}
