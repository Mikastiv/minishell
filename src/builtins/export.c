/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 21:36:30 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/17 00:25:48 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"
#include "environment.h"
#include "errors.h"
#include <stdlib.h>
#include <stdio.h>

static void	add_var(const char *var)
{
	t_string	var_cpy;
	const char	*value;

	var_cpy = ft_str_new(var_name(var));
	value = ft_strchr(var, '=') + 1;
	ft_setenv(ft_str_data(var_cpy), value);
	ft_str_free(var_cpy);
}

static void	print_env(void)
{
	char	**copy;
	size_t	i;

	copy = ft_strarr_dup(g_mini.env);
	ft_strarr_sort(copy);
	i = 0;
	while (copy[i])
		ft_putendl_fd(copy[i++], STDOUT_FILENO);
	ft_strarr_free(copy);
}

void	ft_export(t_node *node)
{
	size_t	i;
	char	*var;

	g_mini.code = SUCCESS;
	if (ft_strarr_size(node->argv) == 1)
	{
		print_env();
		return ;
	}
	var = NULL;
	i = 1;
	while (node->argv[i])
	{
		free(var);
		var = var_name(node->argv[i]);
		if (!is_valid_var_name(var))
		{
			pset_err(EXPORT, node->argv[i], BAD_IDENT, GENERIC_ERR);
			++i;
			continue ;
		}
		add_var(node->argv[i]);
		++i;
	}
	free(var);
}
