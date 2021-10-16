/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 19:10:13 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/16 16:04:10 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void	newline(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_mini.code = INTERRUPT_SIG;
}

void	nothing(int signal)
{
	(void)signal;
}

void	stop_heredoc(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", STDOUT_FILENO);
	exit(INTERRUPT_SIG);
}

void	process_exit_status(int wstatus)
{
	if (WIFEXITED(wstatus))
		g_mini.code = WEXITSTATUS(wstatus);
	if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGQUIT)
	{
		ft_putstr_fd("Quit\n", STDOUT_FILENO);
		g_mini.code = QUIT_SIG;
	}
	if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		g_mini.code = INTERRUPT_SIG;
	}
}
