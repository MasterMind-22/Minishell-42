/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moudrib <moudrib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:32:43 by yonadry           #+#    #+#             */
/*   Updated: 2023/06/13 10:39:24 by moudrib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	syntax_error(char *s2, char e)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	if (s2)
		ft_putstr_fd(s2, 2);
	if (e)
		ft_putchar(e, 2);
	ft_putchar('\n', 2);
	return ;
}

int	search_for_pipe(t_vars *v)
{
	while (v->tmp1)
	{
		if (!ft_strcmp(v->tmp1->type, "PIPE"))
			return (1);
		v->tmp1 = v->tmp1->link;
	}
	return (0);
}
