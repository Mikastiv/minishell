/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 00:42:47 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/17 12:54:28 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment.h"
#include <libft/libft.h>
#include <stdlib.h>
#include <sys/stat.h>

static char	*getcwd_dir(void)
{
	char		cwd[PATH_MAX];
	char		*home;
	t_string	str;
	struct stat	buf;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (ft_strdup(""));
	home = ft_getenv("HOME");
	if (home && ft_strnstr(cwd, home, ft_strlen(home)))
	{
		if (home[ft_strlen(home) - 1] == '/')
			return (ft_strdup(cwd));
		str = ft_str_new_copy(home);
		ft_str_add_back(str, '/');
		ft_str_append_cstr(str, cwd + ft_strlen(home));
		if (stat(ft_str_data(str), &buf) != -1)
		{
			ft_str_free(str);
			return (ft_strjoin("~", cwd + ft_strlen(home)));
		}
	}
	return (ft_strdup(cwd));
}

char	*get_prompt(void)
{
	t_string	prompt;
	char		*dir;

	prompt = ft_str_new_copy("\001"FT_BOLD FT_BRED"\002");
	if (g_mini.user)
		ft_str_append_cstr(prompt, g_mini.user);
	else
		ft_str_append_cstr(prompt, "tty");
	ft_str_append_cstr(prompt, "\001"FT_RST"\002:");
	dir = getcwd_dir();
	ft_str_append_cstr(prompt, "\001"FT_BOLD FT_BBLU"\002");
	ft_str_append_cstr(prompt, dir);
	ft_str_append_cstr(prompt, "\001"FT_RST"\002$ ");
	free(dir);
	return (ft_str_take(prompt));
}
