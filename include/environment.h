/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 00:10:31 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/18 21:19:55 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include <stdbool.h>

# define ENV_PWD "PWD"
# define ENV_OLDPWD "OLDPWD"
# define ENV_HOME "HOME"
# define ENV_USER "USER"
# define ENV_PATH "PATH"

char	*ft_getenv(const char *var);
void	ft_setenv(const char *var, const char *value);
char	*var_name(const char *var);
bool	is_valid_var_name(const char *var);

#endif
