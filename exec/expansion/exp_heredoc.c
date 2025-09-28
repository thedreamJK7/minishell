/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 09:49:49 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/27 18:48:44 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include "minishell.h"

char	*str_before_dollar_s(char **result, char **next_dollar, char **input)
{
	char *new_part;
	char *temp_result;
	int len;

	len = (*next_dollar) - (*input);
	new_part = ft_substr((*input), 0, len);
	temp_result = ft_strjoin(*result, new_part);
	free(*result);
	free(new_part);
	return (temp_result);
}

char *exp_heredoc(char *input, t_shell *shell)
{
	char *result = ft_strdup("");
	char *next_dollar;
	char *temp_result;
	int		len;

    while (ft_strchr(input, '$'))
    {
		next_dollar = ft_strchr(input, '$');
		result = str_before_dollar_s(&result, &next_dollar, &input);
		input = next_dollar + 1;
		char *var_name_end = input;
		while (ft_isalnum(*var_name_end) || *var_name_end == '_')
			var_name_end++;
		len = var_name_end - input;
		char *var_name = ft_substr(input, 0, len);
		char *var_value = get_env_value(shell, var_name);
		if (var_value)
		{
			temp_result = ft_strjoin(result, var_value);
			free(result);
			result = temp_result;
		}
		free(var_name);
		input = var_name_end;
    }
	temp_result = ft_strjoin(result, input);
	free(result);
	result = temp_result;
	return (result);
}

