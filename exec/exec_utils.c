/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:27:24 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/11 17:57:06 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clean_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	close_fd(int in_fd, int out_fd)
{
	if (in_fd > 2)
		close(in_fd);
	if (out_fd > 2)
		close(out_fd);
}

int		check_access(char *path)
{
	if (!access(path, F_OK))
	{
		if (!access(path, X_OK))
			return (0);
		else
			return (COMMAND_NOT_EXECUTABLE);
	}
	return (COMMAND_NOT_FOUND);
}

