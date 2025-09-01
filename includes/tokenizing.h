/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 22:04:04 by javokhir          #+#    #+#             */
/*   Updated: 2025/09/01 16:06:07 by yingzhan         ###   ########.fr       */
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

typedef enum e_quote_type
{
	q_close,
	q_sopen,
	q_dopen,
}	t_quote_type;

typedef struct	s_token
{
		t_token_type	type;
		char			*value; //command
		struct s_token	*next; // next node
}		t_token;


//	Functions
t_token	*ft_tokenize(char *s);
void	print_tokens(t_token *list);
int		change_quote(char c, int *quote);
void	add_tokens(t_token **list, t_token_type type, char *value);
void	specify_tokens_single(char **value, char c, t_token **list);
int		specify_tokens_double(char **value, char c, t_token **list);
void	add_word(char **s, int *quote, t_token **list, char **value);
void	clean_tokens(t_token **list, int exit_flag);

#endif
