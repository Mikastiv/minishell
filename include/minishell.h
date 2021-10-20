/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 13:33:08 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/19 20:09:11 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdint.h>

# ifdef __linux__
#  include <linux/limits.h>
# endif

# ifdef __APPLE__
#  include <limits.h>
# endif

# define SHELL_NAME "minishell"

# define SUCCESS 0
# define GENERIC_ERR 1
# define SYNTAX_ERR 2
# define NOT_EXEC_ERR 126
# define ENVIRONMENT_ERR 127
# define INTERRUPT_SIG 130
# define QUIT_SIG 131

typedef struct s_minishell
{
	char		**envp;
	char		*user;
	uint32_t	code;
	int			stdin_fd;
	int			stdout_fd;
}	t_minishell;

extern t_minishell	g_mini;

void	minishell_init(char *const *envp);
void	minishell_loop(void);
void	minishell_destroy(void);
char	*get_prompt(void);

#endif
