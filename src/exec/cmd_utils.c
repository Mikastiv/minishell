/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 20:10:30 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/26 20:33:22 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include "environment.h"
#include "errors.h"
#include <sys/stat.h>
#include <string.h>

static char	*find_executable(char **dirs, const char *cmd)
{
	struct stat	buf;
	t_string	*str;
	size_t		i;

	i = 0;
	while (dirs[i])
	{
		str = ft_str_new_copy(dirs[i]);
		ft_str_add_back(str, '/');
		ft_str_append_cstr(str, cmd);
		if (stat(ft_str_data(str), &buf) == 0 && !S_ISDIR(buf.st_mode))
			return (ft_str_take(str));
		ft_str_free(str);
		++i;
	}
	return (NULL);
}

static bool	is_in_cwd(const char *cmd)
{
	struct stat	buf;

	if (ft_strchr(cmd, '/') && stat(cmd, &buf) == 0)
	{
		if (S_ISDIR(buf.st_mode))
		{
			errno = EISDIR;
			pset_err(SHELL_NAME, cmd, strerror(errno), NOT_EXEC_ERR);
			return (false);
		}
		return (true);
	}
	return (false);
}

char	*get_cmd_path(const char *cmd)
{
	char	*path;
	char	*absolute;
	char	**dirs;

	if (is_in_cwd(cmd))
		return (ft_strdup(cmd));
	if (errno == EISDIR)
		return (NULL);
	path = ft_getenv(ENV_PATH);
	if (!path)
	{
		pset_err(SHELL_NAME, cmd, CMD_NOT_FOUND, ENVIRONMENT_ERR);
		return (NULL);
	}
	dirs = ft_split(path, ':');
	absolute = find_executable(dirs, cmd);
	if (!absolute)
		pset_err(SHELL_NAME, cmd, CMD_NOT_FOUND, ENVIRONMENT_ERR);
	ft_strarr_free(dirs);
	return (absolute);
}

bool	all_same_cmd(t_node *first)
{
	const char	*cmd;
	t_node		*ptr;

	if (!first->argv[0])
		return (false);
	cmd = first->argv[0];
	ptr = first;
	while (ptr)
	{
		if (ft_strarr_size(ptr->argv) != 1)
			return (false);
		if (ft_lstsize(ptr->redirs) != 0)
			return (false);
		if (!ptr->argv[0])
			return (false);
		if (ft_strcmp(cmd, ptr->argv[0]) != 0)
			return (false);
		ptr = ptr->next;
	}
	return (true);
}
