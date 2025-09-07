/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:includes/expanding.h
/*   Created: 2025/09/02 16:14:06 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/05 14:43:32 by jkubaev          ###   ########.fr       */
=======
/*   Created: 2025/09/05 18:51:25 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/05 19:50:05 by yingzhan         ###   ########.fr       */
>>>>>>> github/main:tokenizing/handle_quotes.c
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	change_quote(char c, int *quote)
{
<<<<<<< HEAD:includes/expanding.h
	char	**env;
	int		exit_code;
}	t_shell;

//void	print_exp(t_node *node);
//void	ft_expand(t_node *root, t_shell *shell);

#endif
=======
	if (c == '\'')
	{
		if (*quote == q_sopen)
			*quote = q_close;
		else if (*quote == q_close)
			*quote = q_sopen;
		else
			return (0);
	}
	else if (c == '"')
	{
		if (*quote == q_dopen)
			*quote = q_close;
		else if (*quote == q_close)
			*quote = q_dopen;
		else
			return (0);
	}
	return (1);
}
>>>>>>> github/main:tokenizing/handle_quotes.c
