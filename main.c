/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:21:52 by yingzhan          #+#    #+#             */
/*   Updated: 2025/08/19 17:30:08 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*input;

	input = readline("minishell$ ");
	if (!input)
	{
		ft_printf("exit");
		exit(1);
	}
	ft_printf("%s\n", input);
	free(input);
}