/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 01:43:42 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/19 00:15:25 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "minishell.h"
#include "builtin.h"
#include <unistd.h>
#include <stdio.h>
#include <libft/libft.h>

static bool	is_builtin(const char *str)
{
	if (!ft_strncmp(str, ECHO, sizeof(ECHO) / sizeof(char)))
		return (true);
	else if (!ft_strncmp(str, PWD, sizeof(PWD) / sizeof(char)))
		return (true);
	else if (!ft_strncmp(str, CD, sizeof(CD) / sizeof(char)))
		return (true);
	else if (!ft_strncmp(str, ENV, sizeof(ENV) / sizeof(char)))
		return (true);
	else if (!ft_strncmp(str, UNSET, sizeof(UNSET) / sizeof(char)))
		return (true);
	else if (!ft_strncmp(str, EXPORT, sizeof(EXPORT) / sizeof(char)))
		return (true);
	else if (!ft_strncmp(str, EXIT, sizeof(EXIT) / sizeof(char)))
		return (true);
	return (false);
}

void	pset_err(const char *prg, const char *v1, const char *v2, int err)
{
	if (prg)
	{
		if (is_builtin(prg))
		{
			ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
		}
		ft_putstr_fd(prg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (v1)
	{
		ft_putstr_fd(v1, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(v2, STDERR_FILENO);
	g_mini.code = (uint32_t)err;
}

void	unexpected_token(const char *token)
{
	t_string	msg;

	msg = ft_str_new_copy("syntax error near unexpected token \'");
	ft_str_append_cstr(msg, token);
	ft_str_add_back(msg, '\'');
	pset_err(SHELL_NAME, NULL, ft_str_data(msg), SYNTAX_ERR);
	ft_str_free(msg);
}
