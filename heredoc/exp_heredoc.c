/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 09:49:49 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/28 19:05:08 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*append_before_dollar(char *result, char **input)
{
	char	*new_part;
	char	*temp_result;
	char	*next_dollar;
	int		len;

	next_dollar = ft_strchr((*input), '$');
	len = next_dollar - (*input);
	new_part = ft_substr_g((*input), 0, len);
	if (!new_part)
		return (printf(ALLOCATION_FAIL), NULL);
	temp_result = ft_strjoin_g(result, new_part);
	if (!temp_result)
		return (printf(ALLOCATION_FAIL), free(new_part), NULL);
	(*input) = next_dollar + 1;
	free(result);
	free(new_part);
	return (temp_result);
}

static char	*extract_var_name(char *input, char **var_name_end)
{
	char	*var_name;
	int		len;

	(*var_name_end) = input;
	while (ft_isalnum((**var_name_end)) || (**var_name_end) == '_')
		(*var_name_end)++;
	len = *var_name_end - input;
	var_name = ft_substr_g(input, 0, len);
	if (!var_name)
		return (printf(ALLOCATION_FAIL), NULL);
	return (var_name);
}

static int	append_var_value(char **var_name, char **result, t_shell *shell)
{
	char	*temp_result;
	char	*var_value;

	var_value = get_env_value(shell, *var_name);
	if (var_value)
	{
		temp_result = ft_strjoin_g(*result, var_value);
		if (!temp_result)
			return (printf(ALLOCATION_FAIL), free(*var_name), free(*result), 1);
		free(*result);
		*result = temp_result;
	}
	free(*var_name);
	return (0);
}

static int	append_result_leftover(char	**result, char **input)
{
	char	*temp_result;

	temp_result = ft_strjoin_g(*result, *input);
	if (!temp_result)
		return (printf(ALLOCATION_FAIL), 1);
	free(*result);
	*result = temp_result;
	return (0);
}

char	*exp_heredoc(char *input, t_shell *shell)
{
	char	*result;
	char	*var_name;
	char	*var_name_end;

	result = ft_strdup("");
	if (!result)
		return (printf(ALLOCATION_FAIL), NULL);
	while (ft_strchr(input, '$'))
	{
		result = append_before_dollar(result, &input);
		if (!result)
			return (NULL);
		var_name = extract_var_name(input, &var_name_end);
		if (!var_name)
			return (printf(ALLOCATION_FAIL), NULL);
		if (append_var_value(&var_name, &result, shell))
			return (NULL);
		input = var_name_end;
	}
	if (append_result_leftover(&result, &input))
		return (NULL);
	return (result);
}
