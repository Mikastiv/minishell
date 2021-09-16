/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 14:46:24 by laube             #+#    #+#             */
/*   Updated: 2021/09/15 22:31:54 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "libft.h"
# include "node.h"
# include <fcntl.h>
# include <unistd.h>
# include <sys/stat.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include "minishell.h"
# include "tokenizer.h"

int		execution_control(t_node *phrase);
int		main_control(t_node *phrase);
char	*get_bin_path(char **envp, char *cmd);
void	pipe_read(void);
void	pipe_write(void);
int		ft_binary(t_node *phrase);
void	ft_exit(t_node *phrase);
int		operation_control(void);
void	clean_fd(void);
void	get_dest(void);
void	clean_fd(void);

#endif
