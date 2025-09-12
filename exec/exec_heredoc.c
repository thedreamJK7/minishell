/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:30:41 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/12 17:58:46 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_heredoc(t_redir_token *redir, int *in_fd)
{
	char	*input;
	int		len_lim;
	int		pfd[2];

	if (pipe(pfd) == -1)
		return (perror("Pipe"), GENERAL_ERROR);
	*in_fd = pfd[0];
	while (1)
	{
		input = readline("> ");
		if (!input)
			break ;
		len_lim = ft_strlen(redir->file);
		if (!ft_strncmp(input, redir->file, len_lim) && (!input[len_lim] || input[len_lim] == '\n'))
		{
			free(input);
			break ;
		}
		if (write(pfd[1], input, ft_strlen(input)) == -1 || write(pfd[1], "\n", 1) == -1)
			return (perror("Write"), GENERAL_ERROR);
		free(input);
	}
	close(pfd[1]);
	return (0);
}