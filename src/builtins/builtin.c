/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 21:10:10 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/19 21:10:17 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

t_builtin	builtin_ptr(const char *str)
{
	if (!ft_strncmp(str, ECHO, sizeof(ECHO) / sizeof(char)))
		return (&ft_echo);
	else if (!ft_strncmp(str, PWD, sizeof(PWD) / sizeof(char)))
		return (&ft_pwd);
	else if (!ft_strncmp(str, CD, sizeof(CD) / sizeof(char)))
		return (&ft_cd);
	else if (!ft_strncmp(str, ENV, sizeof(ENV) / sizeof(char)))
		return (&ft_env);
	else if (!ft_strncmp(str, UNSET, sizeof(UNSET) / sizeof(char)))
		return (&ft_unset);
	else if (!ft_strncmp(str, EXPORT, sizeof(EXPORT) / sizeof(char)))
		return (&ft_export);
	else if (!ft_strncmp(str, EXIT, sizeof(EXIT) / sizeof(char)))
		return (&ft_exit);
	return (NULL);
}
