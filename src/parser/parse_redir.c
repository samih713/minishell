/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 19:01:49 by sabdelra          #+#    #+#             */
/*   Updated: 2023/08/24 00:06:31 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * checking for syntax error in case next token is not a file name,
 * however bash error message takes the last token as the error token,
 * so this is not perfect, this takes the token immediately after redirection
*/
static t_cmd	*token_error(char *q, char *eq)
{
	if (eq - q)
	{
		write(2, "minishell: syntax error near unexpected token `", 48);
		write(2, q, eq - q);
		write(2, "\'\n", 2);
	}
	else
		print_error("syntax error near unexpected token `newline'", NULL);
	g_exit_status = 258;
	return (NULL);
}

static int	*set_open(int mode, int fd)
{
	int		*open_conditions;

	open_conditions = malloc(sizeof(int) * 2);
	open_conditions[MODE] = mode;
	open_conditions[FD] = fd;
	return (open_conditions);
}

static char	*expand_filename(char *q, char *eq, t_env **env_list)
{
	char	*expanded_filename;
	char	*end_of_filename;
	char	*tmp_filename;

	tmp_filename = expand(q, eq, env_list, false);
	end_of_filename = tmp_filename + ft_strlen(tmp_filename);
	expanded_filename = remove_quotes(tmp_filename, end_of_filename);
	free(tmp_filename);
	return (expanded_filename);
}

t_cmd	*parseredir(t_cmd *cmd, char **b_start, char *b_end, t_env **env_list)
{
	int		redirection;
	int		hc_pipe[2];
	char	*q;
	char	*eq;
	char	*expanded_filename;
	char	*end_of_filename;

	while (peek(b_start, b_end, "<>"))
	{
		redirection = get_token(b_start, b_end, 0, 0);
		if (redirection == '-' && verify_pipe(pipe(hc_pipe)))
		{
			cmd = construct_redircmd(cmd, 0, (char *)&hc_pipe[0], set_open(O_RDONLY, STDIN_FILENO));
			get_token(b_start, b_end, &q, &eq);
			here_doc(hc_pipe[1], get_delimiter(q, eq), env_list);
			close(hc_pipe[1]);
		}
		else if (get_token(b_start, b_end, &q, &eq) != 'a')
			return (token_error(q, eq));
		expanded_filename = expand_filename(q, eq, env_list);
		end_of_filename = expanded_filename + ft_strlen(expanded_filename);
		if (redirection == '<')
			cmd = construct_redircmd(cmd, expanded_filename, end_of_filename, set_open(O_RDONLY, STDIN_FILENO));
		else if (redirection == '>')
			cmd = construct_redircmd(cmd, expanded_filename, end_of_filename, set_open(O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO));
		else if (redirection == '+')
			cmd = construct_redircmd(cmd, expanded_filename, end_of_filename, set_open(O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO));
	}
	return (cmd);
}


