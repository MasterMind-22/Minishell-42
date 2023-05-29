/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonadry <yonadry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 11:57:03 by yonadry           #+#    #+#             */
/*   Updated: 2023/05/29 19:02:34 by yonadry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_file(char *file_name, char *type)
{
	int fd;

	if (!ft_strcmp(type, ">"))
	    fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (!ft_strcmp(type, ">>"))
	    fd = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0777);
	if (!ft_strcmp(type, "<"))
	    fd = open(file_name, O_RDONLY, 0777);
	if (fd == -1)
		perror(file_name);
	return (fd);
}

char *is_redir(t_list *list)
{
	if (!ft_strcmp(list->type, "APPEND")
		|| !ft_strcmp(list->type, "OUTFILE")
		|| !ft_strcmp(list->type, "INFILE"))
		return (list->content);
	return (0);
}
 
t_list *handle_file(t_list *list, t_command *f_lst, char *file_name, char *type)
{
	int fd;

	while (list)
	{
		if (!ft_strcmp("VAR", list->type))
		{
			ft_printf_fd("Minishell: %s: ambiguous redirect\n", 2,list->content);
			if (list->link)
				return (list->link);
			return (list);
		}
		if (!ft_strcmp("FILE", list->type))
			file_name = ft_strjoin(file_name, list->content);
		if (file_name && (list->type[0] == 's' || (!list->link)))
		{
			fd = open_file(file_name, type);
			file_name = NULL;
		}
		list = list->link;
	}
	if ((!ft_strcmp(type, ">>") || !ft_strcmp(type, ">")))
		f_lst->fd_out = fd;
	else if (!ft_strcmp(type, "<"))
		f_lst->fd_in = fd;
	if (!ft_strcmp(list->content, "|"))
		return (list);
	return (list);
}

void open_files(t_list *list, t_command **final_list)
{
	char *file_name;
	char *type;
	t_command *tmp;

	tmp = *final_list;
	while (list)
	{
		if (is_redir(list))
		{
			file_name = NULL;
			type = ft_strdup(is_redir(list));
			if (list->link && !ft_strcmp(list->link->type, "space"))
				list = list->link->link;
			else if (list->link)
				list = list->link;
			list = handle_file(list, tmp, file_name, type);
			tmp = tmp->link;
		}
		if (!list)
			break;
		list = list->link;
	}
}