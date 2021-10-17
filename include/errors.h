/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 00:09:45 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/17 00:24:56 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include <sys/errno.h>

# define BAD_IDENT "not a valid identifier"
# define TOO_MANY_ARGS "too many arguments"
# define NUMERIC_REQ "numeric argument required"
# define CMD_NOT_FOUND "command not found"
# define NO_HOME "HOME not set"
# define UNCLOSED_QUOTES "found unclosed quotes"
# define UNCLOSED_DQUOTES "found unclosed double quotes"
# define WARNING "warning"
# define HEREDOC_EOF "here-document was delimited by end-of-file"
# define C_FLAG_ARG_REQ "option requires an argument"
# define UNSUPPORTED_ARG_OPT "unsupported argument or option"

# define ENV_PWD "PWD"
# define ENV_OLDPWD "OLDPWD"
# define ENV_HOME "HOME"

void	pset_err(const char *prg, const char *v1, const char *v2, int err);
void	unexpected_token(const char *token);

#endif
