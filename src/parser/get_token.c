/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabdelra <sabdelra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 07:38:08 by sabdelra          #+#    #+#             */
/*   Updated: 2023/08/04 21:31:17 by sabdelra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool is_opr(char c) {
  return (c == '<' || c == '|' || c == '>' || c == '&' || c == ';');
}

/* returns the type of a token,
helper function for get_token */
	static char find_type(char **scan) {
	int in_quote;

	in_quote = 0;
	if (!**scan)
		return (0);
	else if (is_opr(**scan)) {
		if (!ft_strncmp(*scan, ">>", 2) && ((*scan)++))
			return ('+');
		else if (!ft_strncmp(*scan, "<<", 2) && ((*scan)++))
			return ('-');
		return (**scan);
	}
	if (**scan == '\"' || **scan == '\'')
		in_quote = **scan;
	while (scan[0][1] &&
			(in_quote || (!ft_is_whitespace(scan[0][1]) && !is_opr(scan[0][1])))) {
		*scan += 1;
			if (!(**scan - in_quote))
				return ('q');
	}
	if (in_quote) //! maybe return u to handle unclosed quote
		return (0);
	return ('a');
}

/*
* Returns the type of token as a char
        - '<' returns '<'
        - '>>' returns +
        - 'a' anything thats not an operator
* Advances the b_start to point to the next token in the buffer
* Sets the q and eq pointers to point to the begining and end
* 	of the token respectively
? note: buffer is the return of readline
*/
char get_token(char **buffer_start, char *buffer_end, char **token_start,
               char **token_end) {
  char token_type;
  char *scan;

  scan = *buffer_start;
  while (scan < buffer_end && ft_is_whitespace(*scan))
    scan++;
  if (token_start)
    *token_start = scan;
  token_type = find_type(&scan);
  if (*scan)
    scan++;
  if (token_end)
    *token_end = scan;
  while (scan < buffer_end && ft_is_whitespace(*scan))
    scan++;
  *buffer_start = scan;
  // if (!(token_start - token_end))
  // 	return (0);
  return (token_type);
}
