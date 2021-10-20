/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 00:29:29 by laube             #+#    #+#             */
/*   Updated: 2021/10/19 20:21:58 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "parse.h"
#include "minishell.h"
#include "exec.h"
#include "errors.h"
#include "environment.h"
#include "signals.h"
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>

static void	dispatch_cmd(t_node *node, bool subshell)
{
	if (!ft_strncmp(node->argv[0], ECHO, sizeof(ECHO) / sizeof(char)))
		ft_echo(node);
	else if (!ft_strncmp(node->argv[0], PWD, sizeof(PWD) / sizeof(char)))
		ft_pwd(node);
	else if (!ft_strncmp(node->argv[0], CD, sizeof(CD) / sizeof(char)))
		ft_cd(node);
	else if (!ft_strncmp(node->argv[0], ENV, sizeof(ENV) / sizeof(char)))
		ft_env(node);
	else if (!ft_strncmp(node->argv[0], UNSET, sizeof(UNSET) / sizeof(char)))
		ft_unset(node);
	else if (!ft_strncmp(node->argv[0], EXPORT, sizeof(EXPORT) / sizeof(char)))
		ft_export(node);
	else if (!ft_strncmp(node->argv[0], EXIT, sizeof(EXIT) / sizeof(char)))
		ft_exit(node);
	else if (subshell)
		ft_cmd_subshell(node);
	else
		ft_cmd(node);
}

static void	execute(t_node *node, bool subshell)
{
	if (!op_control(node))
		return ;
	interpolate_arr(node->argv);
	interpolate_redirs(node->redirs);
	if (node->argv[0])
	{
		dispatch_cmd(node, subshell);
		if (!subshell)
			ft_setenv("_", ft_strarr_last(node->argv));
	}
}

static void	execute_subshell(t_node *node)
{
	pid_t	pid;
	int		wstatus;

	if (!op_control(node))
		return ;
	signal(SIGINT, nothing);
	signal(SIGQUIT, nothing);
	pid = fork();
	if (pid == -1)
	{
		pset_err(SHELL_NAME, NULL, strerror(errno), GENERIC_ERR);
		return ;
	}
	if (pid == 0)
	{
		execute(node, true);
		exit((int)g_mini.code);
	}
	waitpid(pid, &wstatus, 0);
	signal(SIGINT, newline);
	signal(SIGQUIT, SIG_IGN);
	process_exit_status(wstatus);
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
	bool	has_pipe;

	start = cmds;
	has_pipe = cmds->next;
	init_pipes(start);
	error = process_heredocs(cmds);
	while (!error && cmds)
	{
		if (has_pipe)
			execute_subshell(cmds);
		else
			execute(cmds, false);
		fd_reset();
		if (g_mini.code == QUIT_SIG || g_mini.code == INTERRUPT_SIG)
			break ;
		cmds = cmds->next;
	}
	close_pipes(start);
}
