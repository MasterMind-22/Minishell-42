/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonadry <yonadry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:32:32 by yonadry           #+#    #+#             */
/*   Updated: 2023/05/06 19:06:56 by yonadry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_space(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

void switch_space(char *input, int x)
{
	t_vars v;

	v.i = -1;
	while (input[++v.i] && x)
	{
		if (input[v.i] == '\'')
		{
			while (input[++v.i] && input[v.i] != '\'')
				if (is_space(input[v.i]))
					input[v.i] *= -1;
		}
		else if (input[v.i] == '\"')
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

char is_quote(char *input)
{
	int i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '\"' || input[i] == '\'')
			return input[i];
	}
	return 0;
}

void handle_quotes(t_vars *v, t_list **lst, char c)
{
	int start;
	int end;

	if (v->arr[v->i][v->j] && v->arr[v->i][v->j] == c)
	{
		start = v->j;
		v->j++;
		while (v->arr[v->i][v->j] && v->arr[v->i][v->j] != c)
			v->j++;
		end = v->j - start;
		ft_lstadd_back(lst, ft_lstnew(ft_substr(v->arr[v->i], start, end+1)));
		// if(v->arr[v->i+1])
		// 	ft_lstadd_back(&lst, ft_lstnew(" "));
		v->j++;
	}
	else if (v->arr[v->i][v->j] && v->arr[v->i][v->j] == '\'')
		return;
	else if (v->arr[v->i][v->j])
	{
		start = v->j;
		while (v->arr[v->i][v->j] && v->arr[v->i][v->j] != c)
			v->j++;
		end = v->j - start;
		ft_lstadd_back(lst, ft_lstnew(ft_substr(v->arr[v->i], start, end)));
		// v->j++;
	}
	// else if(!v->arr[v->i][v->j])
	// 	ft_lstadd_back(&lst, ft_lstnew(" "));
}


void ft_split_input(char *input)
{
	t_list *lst = NULL;
	t_vars v;

	v.i = 0;
	v.j = 0;
	switch_space(input, 1);
	v.arr = ft_split(input, " \t");
	while (v.arr[v.i])
	{
		if (v.arr[v.i] && is_quote(v.arr[v.i]))
		{
			v.j = 0;
			while (v.arr[v.i][v.j])
			{
				handle_quotes(&v, &lst, is_quote(&v.arr[v.i][v.j]));
				// v.arr[v.i] = ft_substr(v.arr[v.i], v.j, ft_strlen(&v.arr[v.i][v.j]));
				// printf("<<%s>>\n", v.arr[v.i]);
			}
			v.i++;
		}
		else
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
		// if (lst->content[0] < 0)
		// 	lst->content[0] *= -1;
		switch_space(lst->content, 0);
		lst = lst->link;
	}
	while (tmp)
	{
		printf("|%s|\n", tmp->content);
		tmp = tmp->link;
	}
}