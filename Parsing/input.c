/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonadry <yonadry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:32:32 by yonadry           #+#    #+#             */
/*   Updated: 2023/05/05 17:36:19 by yonadry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_space(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ft_count_arguments(char *input)
{
	t_vars	var;

	var.i = 0;
	var.count = 0;
	while (input[var.i])
	{
		while (input[var.i] && is_space(input[var.i]))
			var.i++;
		if (input[var.i] == '\"')
		{
			var.i++;
			var.count++;
			while (input[var.i] && input[var.i] != '\"')
				var.i++;
			var.i++;
		}
		else if (input[var.i])
		{
			while (input[var.i] && input[var.i] != ' ' && input[var.i] != '\"')
				var.i++;
			var.count++;
		}
	}
	return (var.count);
}

char is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return c;
	return 0;
}
void switch_space(char *input, int x)
{
	t_vars v;

	v.i = -1;
	while (input[++v.i] && x)
	{
		if (input[v.i] == '\"')
		{
			while (input[++v.i] && input[v.i] != '\"')
				if (is_space(input[v.i]))
					input[v.i] *= -1;
		}
	}
	while (input[++v.i] && !x)
	{
		if (input[v.i] < 0)
			input[v.i] *= -1;
	}
}

void ft_split_input(char *input)
{
	t_list *lst = NULL;
	t_vars v;
	int start;
	int end;

	v.i = 0;
	v.j = 0;
	switch_space(input, 1);
	v.arr = ft_split(input, " \t");
	while (v.arr[v.i])
	{
		if (v.arr[v.i] && (ft_strchr(v.arr[v.i], '\"') || v.arr[v.i][0] == '\"'))
		{
			v.j = 0;
			while (v.arr[v.i][v.j])
			{
				if (v.arr[v.i][v.j] && v.arr[v.i][v.j] == '\"')
				{
					start = v.j;
					v.j++;
					while (v.arr[v.i][v.j] != '\"')
						v.j++;
					end = v.j - start;
					ft_lstadd_back(&lst, ft_lstnew(ft_substr(v.arr[v.i], start, end+1)));
					// if(v.arr[v.i+1])
					// 	ft_lstadd_back(&lst, ft_lstnew(" "));
					v.j++;
				}
				else if (v.arr[v.i][v.j])
				{
					start = v.j;
					while (v.arr[v.i][v.j] && v.arr[v.i][v.j] != '\"')
						v.j++;
					end = v.j - start;
					ft_lstadd_back(&lst, ft_lstnew(ft_substr(v.arr[v.i], start, end)));
					// v.j++;
				}
				// else if(!v.arr[v.i][v.j])
				// 	ft_lstadd_back(&lst, ft_lstnew(" "));
			}
			v.i++;
		}
		else if (v.arr[v.i])
		{
			ft_lstadd_back(&lst, ft_lstnew(v.arr[v.i]));
			// if (v.arr[v.i+1])
			// 	ft_lstadd_back(&lst, ft_lstnew(" "));
			v.i++;
		}
		if (v.arr[v.i])
			ft_lstadd_back(&lst, ft_lstnew(" "));
	}
	t_list *tmp = lst;
	while (lst)
	{
		switch_space(lst->content, 0);
		lst = lst->link;
	}
	while (tmp)
	{
		printf("|%s|\n", tmp->content);
		tmp = tmp->link;
	}
}