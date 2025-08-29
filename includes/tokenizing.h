/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 22:04:04 by javokhir          #+#    #+#             */
/*   Updated: 2025/08/29 12:01:53 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZING_H
# define TOKENIZING_H

typedef enum e_token_type
{
	T_WORD,//	normal word
	T_PIPE,//	|
	T_GREAT,//	>
	T_LESS, //	<
	T_DGREAT,//	>>
	T_DLESS,//	<<
	T_EOF,//	end of file
	T_VAR//		variable to be expanded
}		t_token_type;

typedef struct	s_token
{
		t_token_type	type;
		char			*value; //command
		struct s_token	*next; // next node
}		t_token;


//	Functions
t_token	*ft_tokenize(char *s);
void	print_tokens(t_token *list);
void	add_tokens(t_token **list, t_token_type type, char *value);
int		specify_tokens(char c, t_token **list, int single);
int		handle_quotes(char *s, char c, t_token **list);
int		handle_words(char *s, t_token **list);
int		handle_dollar(char *s, t_token **list);
void	clean_tokens(t_token **list);

#endif
