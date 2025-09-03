/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:16:19 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/03 17:15:58 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_getenv(t_shell *shell, char *s)
{
	int		i;
	int		len;

	if (!shell || !shell->env || !s)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	while (shell->env[i])
	{
		if (!ft_strncmp(s, shell->env[i], len) && shell->env[i][len] == '=')
			return (&shell->env[i][len + 1]);
		i++;
	}
	return (NULL);
}

void	expand_var(t_token **token, t_shell *shell)
{
	t_token	*new;
	char	*var;
	char	*value;

	if (!ft_strncmp((*token)->value, "?", 1))
		value = ft_itoa(shell->exit_code);
	else
		var = ft_getenv(shell, (*token)->value);
	new = malloc(sizeof(t_token));
	if (!new)
		return ;//need clean up memory
	if (!var)
		value = ft_strdup("");
	else
		value = ft_strdup(var);
	if (!value)
		return ;//need clean up memory
	new->value = value;
	new->next = (*token)->next;
	new->type = T_WORD;
	free((*token)->value);
	free(*token);
	*token = new;
}

char	*create_new_buffer(t_token *list)
{
	int		i;
	t_token	*tmp;
	char	*buffer;

	i = 0;
	tmp = list;
	while (tmp)
	{
		i += ft_strlen(tmp->value);
		tmp = tmp->next;
	}
	buffer = ft_calloc(i + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	buffer[i] = '\0';
	while (list)
	{
		ft_strlcat(buffer, list->value, ft_strlen(list->value));
		list = list->next;
	}
	return (buffer);
}

void	merge_token(t_token **list)
{
	t_token	*tmp;
	t_token	*cur;
	char	*new_value;

	tmp = *list;
	new_value = create_new_buffer(tmp);
	if (!new_value)
		return ; //clean up memory
	free(tmp->value);
	tmp->value = new_value;
	tmp = tmp->next;
	while (tmp)
	{
		cur = tmp->next;
		free (tmp->value);
		free (tmp);
		tmp = cur;
	}
	tmp->next = NULL;
}

void	ft_expand(t_node *root, t_shell *shell)
{
	t_token *tmp_token;

	if (!root)
		return ;
	if (root->type == COMMAND)
	{
		tmp_token = root->cmd.args;
		while (tmp_token)
		{
			if (tmp_token->type == T_VAR)
				expand_var(&tmp_token, shell);
			tmp_token = tmp_token->next;
		}
		merge_token(&root->cmd.args);
	}
	else if (root->type == PIPE)
	{
		ft_expand(root->pipe.left, shell);
		ft_expand(root->pipe.right, shell);
	}
}