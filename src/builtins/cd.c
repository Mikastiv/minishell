/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 21:33:13 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/22 16:10:33 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"
#include "errors.h"
#include "environment.h"
#include <string.h>
#include <sys/errno.h>
#include <stdlib.h>

static void	update_pwd(void)
{
	char	*cwd;
	char	*oldpwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		pset_err(FT_CD, NULL, strerror(errno), GENERIC_ERR);
		return ;
	}
	oldpwd = ft_getenv(ENV_PWD);
	if (oldpwd)
		ft_setenv(ENV_OLDPWD, oldpwd);
	ft_setenv(ENV_PWD, cwd);
	free(cwd);
	g_mini.code = SUCCESS;
}

void	ft_cd(t_node *node)
{
	if (ft_strarr_size(node->argv) > 1)
	{
		if (ft_strarr_size(node->argv) > 2)
		{
			pset_err(FT_CD, NULL, TOO_MANY_ARGS, GENERIC_ERR);
			return ;
		}
		if (chdir(node->argv[1]) == -1)
		{
			pset_err(FT_CD, strerror(errno), node->argv[1], GENERIC_ERR);
			return ;
		}
	}
	else if (!ft_getenv(ENV_HOME))
	{
		pset_err(FT_CD, NULL, NO_HOME, GENERIC_ERR);
		return ;
	}
	else if (chdir(ft_getenv(ENV_HOME)) == -1)
	{
		pset_err(FT_CD, NULL, strerror(errno), GENERIC_ERR);
		return ;
	}
	update_pwd();
}
