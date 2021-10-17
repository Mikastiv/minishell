/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 21:32:32 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/17 00:26:02 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"
#include "errors.h"
#include <string.h>
#include <stdio.h>

#ifdef __linux__
# include <linux/limits.h>
#endif

#ifdef __APPLE__
# include <limits.h>
#endif

void	ft_pwd(t_node *node)
{
	char	cwd[PATH_MAX];

	(void)node;
	if (getcwd(cwd, PATH_MAX) != NULL)
		ft_putendl_fd(cwd, STDOUT_FILENO);
	else
	{
		pset_err(PWD, NULL, strerror(errno), GENERIC_ERR);
		return ;
	}
	g_mini.code = SUCCESS;
}
