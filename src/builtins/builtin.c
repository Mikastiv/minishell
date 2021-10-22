/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 21:10:10 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/22 16:13:02 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

t_builtin	builtin_ptr(const char *str)
{
	if (!ft_strncmp(str, FT_ECHO, sizeof(FT_ECHO) / sizeof(char)))
		return (&ft_echo);
	else if (!ft_strncmp(str, FT_PWD, sizeof(FT_PWD) / sizeof(char)))
		return (&ft_pwd);
	else if (!ft_strncmp(str, FT_CD, sizeof(FT_CD) / sizeof(char)))
		return (&ft_cd);
	else if (!ft_strncmp(str, FT_ENV, sizeof(FT_ENV) / sizeof(char)))
		return (&ft_env);
	else if (!ft_strncmp(str, FT_UNSET, sizeof(FT_UNSET) / sizeof(char)))
		return (&ft_unset);
	else if (!ft_strncmp(str, FT_EXPORT, sizeof(FT_EXPORT) / sizeof(char)))
		return (&ft_export);
	else if (!ft_strncmp(str, FT_EXIT, sizeof(FT_EXIT) / sizeof(char)))
		return (&ft_exit);
	return (NULL);
}
