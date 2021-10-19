/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 20:37:15 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/19 00:13:46 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_type	get_type(t_string token)
{
	if (!ft_strncmp(ft_str_data(token), "|", ft_str_len(token)))
		return (PIPE);
	if (!ft_strncmp(ft_str_data(token), "<", ft_str_len(token)))
		return (INPUT);
	if (!ft_strncmp(ft_str_data(token), "<<", ft_str_len(token)))
		return (HEREDOC);
	if (!ft_strncmp(ft_str_data(token), ">", ft_str_len(token)))
		return (OUTPUT);
	if (!ft_strncmp(ft_str_data(token), ">>", ft_str_len(token)))
		return (APPEND);
	return (STRING);
}

bool	is_redirection(t_type type)
{
	if (type == OUTPUT || type == APPEND
		|| type == INPUT || type == HEREDOC)
		return (true);
	return (false);
}
