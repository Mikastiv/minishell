/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 14:46:24 by laube             #+#    #+#             */
/*   Updated: 2021/10/18 20:33:05 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "node.h"

void	process_cmd(t_node *cmds);
void	ft_cmd(t_node *node, bool update_);
bool	op_control(t_node *cmds);
bool	exec_redirections(t_list *redirs, int *pipe_fd);
bool	exec_heredocs(t_list *redirs, int stdin_fd);

void	fd_reset(void);
void	init_pipes(t_node *cmds);
void	close_pipes(t_node *cmds);

#endif
