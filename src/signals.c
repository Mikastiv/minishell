/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 19:10:13 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/19 21:16:02 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "minishell.h"
#include "errors.h"
#include <libft/libft.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void	newline(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", STDERR_FILENO);
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
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(INTERRUPT_SIG);
}

void	process_exit_status(int wstatus)
{
	if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGQUIT)
	{
		ft_putstr_fd("Quit\n", STDERR_FILENO);
		g_mini.code = QUIT_SIG;
	}
	else if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGINT)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		g_mini.code = INTERRUPT_SIG;
	}
	else if (WIFEXITED(wstatus))
		g_mini.code = WEXITSTATUS(wstatus);
	else
		g_mini.code = GENERIC_ERR;
}
