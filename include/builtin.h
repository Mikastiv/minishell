/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 20:45:01 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/19 21:13:56 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "node.h"

# define ECHO "echo"
# define PWD "pwd"
# define CD "cd"
# define EXPORT "export"
# define UNSET "unset"
# define ENV "env"
# define EXIT "exit"

typedef void	(*t_builtin)(t_node *);

t_builtin	builtin_ptr(const char *str);
void		ft_echo(t_node *node);
void		ft_cd(t_node *node);
void		ft_unset(t_node *node);
void		ft_export(t_node *node);
void		ft_pwd(t_node *node);
void		ft_env(t_node *node);
void		ft_exit(t_node *node);

#endif
