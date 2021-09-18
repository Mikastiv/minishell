/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_operator2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 16:19:08 by laube             #+#    #+#             */
/*   Updated: 2021/09/17 20:23:21 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	clean_fd(void)
{
	dup2(g_mini.saved_stdin, 0);
	dup2(g_mini.saved_stdout, 1);
}

void	dest_pipe_write(void)
{
	if (pipe(g_mini.fd) == -1)
		print_error("Pipe error");
	dup2(g_mini.fd[1], 1);
	close(g_mini.fd[1]);
	g_mini.fd[1] = -1;
}

void	dest_red_output(void)
{
	int			open_fd;
	t_node	*phrase_og;

	phrase_og = g_mini.phrase;
	while (g_mini.phrase->op == OUTPUT || g_mini.phrase->op == APPEND)
	{
		if (g_mini.phrase->op == OUTPUT)
			open_fd = open(g_mini.phrase->next->name,
					O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (g_mini.phrase->op == APPEND)
			open_fd = open(g_mini.phrase->next->name,
					O_RDWR | O_APPEND | O_CREAT, 0644);
		dup2(open_fd, 1);
		close(open_fd);
		execution_control(phrase_og);
		g_mini.phrase = g_mini.phrase->next;
	}
	g_minishell.phrase = g_minishell.phrase->next;
	clean_fd();
	exit(0);
}

void	get_dest(void)
{
	if (g_mini.phrase->op == PIPE)
		dest_pipe_write();
	if (g_mini.phrase->op == OUTPUT || g_mini.phrase->op == APPEND)
		dest_red_output();
}
