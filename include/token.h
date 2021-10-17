/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 00:14:42 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/17 00:15:16 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <libft/libft.h>

typedef enum e_type
{
	PIPE,
	OUTPUT,
	APPEND,
	INPUT,
	HEREDOC,
	STRING,
}	t_type;

t_type	get_type(t_string token);
bool	is_redirection(t_type type);

#endif
