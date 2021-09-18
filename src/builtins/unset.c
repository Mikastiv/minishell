/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 21:34:45 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/18 15:54:28 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"

static void	remove_var(const char *var)
{
	size_t		i;
	t_string	var_cpy;

	var_cpy = ft_str_new_copy(var);
	ft_str_add_back(var_cpy, '=');
	i = 0;
	while (g_mini.env[i])
	{
		if (ft_str_cmp_cstr(var_cpy, g_mini.env[i], ft_str_len(var_cpy)) == 0)
		{
			ft_shrink_strarr(g_mini.env, i);
			ft_str_free(var_cpy);
			return ;
		}
		++i;
	}
	ft_str_free(var_cpy);
}

void	ft_unset(t_node *node)
{
	size_t	i;

	i = 1;
	while (node->args[i])
	{
		if (!is_valid_var_name(node->args[i]))
		{
			pset_err(UNSET, node->args[i],
				"not a valid identifier", GENERIC_ERR);
			++i;
			continue ;
		}
		remove_var(node->args[i]);
		++i;
	}
	g_mini.code = SUCCESS;
}
