/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 19:50:04 by jkubaev           #+#    #+#             */
/*   Updated: 2025/08/22 13:10:14 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef enum e_token_type
{
	T_WORD,//	normal word
	T_PIPE,//	|
	T_GREAT,//	>
	T_LESS, //	<
	T_DGREAT,//	>>
	T_DLESS,//	<<
	T_EOF//	end of file
}	t_token_type;

typedef	struct s_token
{
	t_token_type	type;
	char			*value; //command
	struct s_token	*next; // next node
}	t_token;

// Functions
void	ft_tokenize(char *s);
int		specify_tokens(char c, t_token **list, int single);
int		handle_quotes(char *s, char c, t_token **list);
int		handle_words(char *s, t_token **list);
void	clean_tokens(t_token **list);
void	print_tokens(t_token *list);//should be removed later

#endif