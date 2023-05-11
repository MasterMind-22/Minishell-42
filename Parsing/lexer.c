/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonadry <yonadry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:22:22 by moudrib           #+#    #+#             */
/*   Updated: 2023/05/09 19:41:52 by yonadry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirections(t_list *tmp)
{
}

void	lexer(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->prev == NULL && ft_strcmp(tmp->content, ">>")
			&& ft_strcmp(tmp->content, ">") && ft_strcmp(tmp->content, "<<"))
			tmp->type = ft_strdup("COMMAND");
		else if (!ft_strcmp(tmp->content, "|"))
			tmp->type = ft_strdup("PIPE");
		else if (!ft_strcmp(tmp->content, " "))
			tmp->type = ft_strdup("SPACE");
		else if (tmp->content[0] == '-')
			tmp->type = ft_strdup("FLAG");
		else if (tmp->content[0] == '\"')
			tmp->type = ft_strdup("DOUBLE_Q");
		else if (tmp->content[0] == '\'')
			tmp->type = ft_strdup("SINGLE_Q");
		else if (!ft_strcmp(tmp->content, "<<"))
			tmp->type = ft_strdup("HEREDOC");
		else if (!ft_strcmp(tmp->content, ">>"))
			tmp->type = ft_strdup("APPEND");
		else if (!ft_strcmp(tmp->content, ">"))
			tmp->type = ft_strdup("OUTPUT");
		else if (!ft_strcmp(tmp->content, "<"))
			tmp->type = ft_strdup("INPUT");
		else if (!ft_strcmp(tmp->prev->content, "<")
				|| !ft_strcmp(tmp->prev->prev->content, "<")
				|| !ft_strcmp(tmp->prev->content, ">")
				|| !ft_strcmp(tmp->prev->prev->content, ">")
				|| !ft_strcmp(tmp->prev->content, ">>")
				|| !ft_strcmp(tmp->prev->prev->content, ">>"))
			tmp->type = ft_strdup("FILE");
		else if (!ft_strcmp(tmp->prev->content, "<<")
				|| !ft_strcmp(tmp->prev->prev->content, "<<"))
			tmp->type = ft_strdup("DELIMITER");
		else
			tmp->type = ft_strdup("COMMAND");
		tmp = tmp->link;
	}
}
