/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 01:31:53 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/22 15:40:44 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include "parse.h"
#include "errors.h"
#include "signals.h"
#include "token.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <signal.h>
#include <sys/wait.h>

static void	print_warning(const char *delim)
{
	t_string	msg;

	msg = ft_str_new_copy(HEREDOC_EOF);
	ft_str_append_cstr(msg, " (wanted '");
	ft_str_append_cstr(msg, delim);
	ft_str_append_cstr(msg, "')");
	pset_err(SHELL_NAME, WARNING, ft_str_data(msg), SUCCESS);
	ft_str_free(msg);
}

static void	exec_heredoc(const char *delim, int *heredoc_fd)
{
	char	*line;

	signal(SIGINT, stop_heredoc);
	line = readline("> ");
	while (line)
	{
		if (ft_strcmp(line, delim) == 0)
		{
			close(heredoc_fd[1]);
			close(heredoc_fd[0]);
			break ;
		}
		ft_putendl_fd(line, heredoc_fd[1]);
		free(line);
		line = readline("> ");
	}
	if (!line)
		print_warning(delim);
	free(line);
	exit(SUCCESS);
}

static bool	redir_heredoc(t_redir *redir, int fd)
{
	int		heredoc_fd[2];
	pid_t	pid;
	int		wstatus;

	redir->file = interpolate(redir->file);
	signal(SIGINT, nothing);
	pipe(heredoc_fd);
	pid = fork();
	if (pid == -1)
		pset_err(SHELL_NAME, NULL, strerror(errno), GENERIC_ERR);
	if (pid == 0)
		exec_heredoc(redir->file, heredoc_fd);
	waitpid(pid, &wstatus, 0);
	signal(SIGINT, newline);
	if (WIFEXITED(wstatus))
		g_mini.code = WEXITSTATUS(wstatus);
	dup2(heredoc_fd[0], fd);
	close(heredoc_fd[1]);
	close(heredoc_fd[0]);
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == INTERRUPT_SIG)
		return (false);
	return (true);
}

bool	exec_heredocs(t_list *redirs, int stdin_fd)
{
	t_redir	*redir;

	while (redirs)
	{
		redir = redirs->content;
		if (redir->type == HEREDOC)
		{
			if (!redir_heredoc(redir, stdin_fd))
				return (false);
		}
		ft_lstnext(&redirs);
	}
	return (true);
}
