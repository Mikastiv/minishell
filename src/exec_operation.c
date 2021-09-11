/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_operation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 18:54:03 by laube             #+#    #+#             */
/*   Updated: 2021/09/10 21:09:31 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	clean_fd(void)
{
	dup2(g_minishell.saved_stdin, 0);
	dup2(g_minishell.saved_stdout, 1);
}

void	src_pipe_read(void)
{
	// DEBUGGIN: CHECKING FOR LOOSE FDs
	if (g_minishell.fd[0] == -1)
		printf("OUCH!: src_pipe_read fd[0] is -1\n");
	// END OF DEBUGGIN

	dup2(g_minishell.fd[0], 0);
	close(g_minishell.fd[0]);
	g_minishell.fd[0] = -1;
}

void	src_red_input(void)
{
	int		open_fd;
	char	*line;

	open_fd = open(g_minishell.phrase->next->name, O_RDONLY);
	while (get_next_line(open_fd, &line) > 0)
	{
		ft_putstr_fd(line, g_minishell.fd[1]);
		ft_putstr_fd("\n", g_minishell.fd[1]);
	}
	close(open_fd);
}

void	src_heredoc(void)
{
	char	*line;
	char	*limiter;
	int		ret;

	if (g_minishell.phrase->next)
		limiter = g_minishell.phrase->next->name;
	else
		limiter = NULL;
	ft_putstr_fd("> ", 1);
	while ((ret = get_next_line(0, &line)) > 0)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			return ;
		}
		ft_putstr_fd("> ", 1);
		ft_putstr_fd(line, g_minishell.fd[1]);
		ft_putstr_fd("\n", g_minishell.fd[1]);
	}
}

void	get_source(void)
{
	t_phrase	*phrase_og;

	phrase_og = g_minishell.phrase;
	if (g_minishell.phrase->prev && g_minishell.phrase->prev->op == PIPE)
		src_pipe_read();
	if (g_minishell.phrase->op == INPUT || g_minishell.phrase->op == READ)
	{
		// DEBUGGIN: CHECKING FOR LOOSE FDs
		if (g_minishell.fd[0] == -1 || g_minishell.fd[1] == -1)
			printf("OUCH!: get_source fd[0] or fd[1] is -1\n");
		// END OF DEBUGGIN

		if (pipe(g_minishell.fd) != 0)
			print_error("pipe failed in src_heredoc");
		while (g_minishell.phrase->op == INPUT || g_minishell.phrase->op == READ)
		{
			if (g_minishell.phrase->op == INPUT)
				src_red_input();
			if (g_minishell.phrase->op == READ)
				src_heredoc();
			g_minishell.phrase = g_minishell.phrase->next;
		}
		dup2(g_minishell.fd[0], 0);
		//close(g_minishell.fd[0]);
		g_minishell.fd[0] = -1;
		close(g_minishell.fd[1]);
		g_minishell.fd[1] = -1;
	}
	g_minishell.phrase = phrase_og;
}

void	dest_pipe_write(void)
{
	
	if (pipe(g_minishell.fd) == -1)
		print_error("Pipe error");
	dup2(g_minishell.fd[1], 1);

	// DEBUGGIN: CHECKING FOR LOOSE FDs
		if (g_minishell.fd[1] == -1)
			printf("OUCH!: dest_pipe_write fd[1] is -1\n");
	// END OF DEBUGGIN
	
	close(g_minishell.fd[1]);
	g_minishell.fd[1] = -1;
}

void	dest_red_output(void)
{
	int	open_fd;
	t_phrase	*phrase_og;
	struct stat	fstat_buff;

	(void)fstat_buff;
	phrase_og = g_minishell.phrase;
	while (g_minishell.phrase->op == OUTPUT || g_minishell.phrase->op == APPEND)
	{
		/*
		fstat(0, &fstat_buff);
		printf("topfstat st_size: %lld\n", fstat_buff.st_size);
		*/
		if (g_minishell.phrase->op == OUTPUT)
			open_fd = open(g_minishell.phrase->next->name, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (g_minishell.phrase->op == APPEND)
			open_fd = open(g_minishell.phrase->next->name, O_RDWR | O_APPEND | O_CREAT, 0644);
		dup2(open_fd, 1);
		close(open_fd);
		execution_control(phrase_og);
		/* 
		testing below
		dup2(g_minishell.saved_stdout, 1);
		fstat(0, &fstat_buff);
		printf("bottomfstat st_size: %lld\n", fstat_buff.st_size);
		testing above 
		*/
		g_minishell.phrase = g_minishell.phrase->next;
	}
	clean_fd();
}

void	get_dest(void)
{
	if (g_minishell.phrase->op == PIPE)
		dest_pipe_write();
	if (g_minishell.phrase->op == OUTPUT || g_minishell.phrase->op == APPEND)
		dest_red_output();
}

void	operation_control(void)
{
	get_source();
	get_dest();
	execution_control(g_minishell.phrase);
	clean_fd();
	while (g_minishell.phrase->op == INPUT || g_minishell.phrase->op == READ)
		g_minishell.phrase = g_minishell.phrase->next;
}
