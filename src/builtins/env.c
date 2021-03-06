/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 21:34:03 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/22 16:12:16 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"
#include "errors.h"
#include <stdio.h>

void	ft_env(t_node *node)
{
	size_t	i;

	if (ft_strarr_size(node->argv) > 1)
	{
		pset_err(FT_ENV, NULL, TOO_MANY_ARGS, GENERIC_ERR);
		return ;
	}
	i = 0;
	while (g_mini.envp[i])
	{
		ft_putendl_fd(g_mini.envp[i], STDOUT_FILENO);
		++i;
	}
	g_mini.code = SUCCESS;
}
