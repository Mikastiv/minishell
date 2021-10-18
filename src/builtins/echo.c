/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 21:31:35 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/18 19:10:38 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"
#include "errors.h"
#include <stdio.h>

static void	print_all(char *const *args, bool nl)
{
	size_t	i;

	i = 0;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		++i;
		if (args[i])
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (nl)
		ft_putstr_fd("\n", STDOUT_FILENO);
}

static bool	valid_flag(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		++i;
	}
	return (true);
}

void	ft_echo(t_node *node)
{
	bool	nl;
	size_t	i;

	nl = true;
	i = 1;
	while (node->argv[i] && node->argv[i][0] == '-' && node->argv[i][1])
	{
		if (!valid_flag(&node->argv[i][1]))
			break ;
		nl = false;
		++i;
	}
	print_all(&node->argv[i], nl);
	g_mini.code = SUCCESS;
}
