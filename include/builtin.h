/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 20:45:01 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/22 16:12:53 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "node.h"

# define FT_ECHO "echo"
# define FT_PWD "pwd"
# define FT_CD "cd"
# define FT_EXPORT "export"
# define FT_UNSET "unset"
# define FT_ENV "env"
# define FT_EXIT "exit"

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
