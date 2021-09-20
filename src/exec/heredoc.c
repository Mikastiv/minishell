/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 01:31:53 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/20 15:29:36 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include <stdlib.h>
#include <readline/readline.h>

void	stop_heredoc(int signal)
{
	(void)signal;
	g_mini.code = 130;
	write(1, "\n", 1);
	exit(130);
}

void	exec_heredoc(char **line, char *limiter, int *heredoc_fd)
{
	signal(SIGINT, stop_heredoc);
	*line = readline("> ");
	while (*line)
	{
		if (ft_strncmp(*line, limiter, ft_strlen(limiter)) == 0)
		{
			close(heredoc_fd[1]);
			close(heredoc_fd[0]);
			break ;
		}
		ft_putstr_fd(*line, heredoc_fd[1]);
		ft_putstr_fd("\n", heredoc_fd[1]);
		free(*line);
		*line = readline("> ");
	}
	free(*line);
	exit(0);
}

void	redir_heredoc(t_redir *redir)
{
	char	*limiter;
	char	*line;
	int		heredoc_fd[2];
	int		pid;

	(void)pid;
	limiter = redir->file;
	signal(SIGINT, SIG_IGN);
	pipe(heredoc_fd);
	pid = fork();
	if (pid == 0)
		exec_heredoc(&line, limiter, heredoc_fd);
	wait(0);
	signal(SIGINT, newline);
	dup2(heredoc_fd[0], STDIN_FILENO);
	close(heredoc_fd[1]);
	close(heredoc_fd[0]);
}
