/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 22:04:04 by javokhir          #+#    #+#             */
/*   Updated: 2025/09/27 17:07:00 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZING_H
# define TOKENIZING_H

# define ERROR "Syntax error: Unclosed quote\n"

# include "minishell.h"

typedef enum e_token_type
{
	T_WORD,//	normal word
	T_PIPE,//	|
	T_GREAT,//	>
	T_LESS, //	<
	T_DGREAT,//	>>
	T_DLESS,//	<<
	T_EOF,//	end of file
	T_VAR,
}		t_token_type;

typedef enum e_quote_type
{
	q_close,
	q_sopen,
	q_dopen,
}	t_quote_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value; //command
	struct s_token	*next; // next node
}		t_token;

//	Functions
t_token	*ft_tokenize(char *s, t_shell *shell);
char	*handle_dollar(char **s, t_shell *shell, t_token **list);
int		change_quote(char c, int *quote);
void	add_tokens(t_token **list, t_token_type type, char *value);
void	ft_realloc(int pos, char c, char **value, t_token **list);
int		break_condition(int quote, char c);
int		get_in_quote(int quote, char c);
int		is_variable(int quote, char *s);
int		specify_tokens(char *s, t_token **list);
int		handle_words(char *s, int *quote, t_token **list, t_shell *shell);
void	clean_tokens(t_token **list, int exit_flag);
char	*get_env_value(t_shell *shell, char *s);

#endif
