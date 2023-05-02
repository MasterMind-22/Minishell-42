/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonadry <yonadry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:11:44 by yonadry           #+#    #+#             */
/*   Updated: 2023/05/01 19:05:48 by yonadry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_space(int c)
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

void	ft_split_input(char *input)
{
	int		i;
	char	**arr;
	t_list *lst;

	i = 0;
	arr = ft_split(input, " 	");
	lst = NULL;
	while (arr[i])
	{
		if (ft_strchr(arr[i], '\"') || ft_strchr(arr[i], '\''))
		{
			ft_lstadd_back(&lst, ft_lstnew(arr[i]));
			while (!ft_strchr(arr[++i], '\"') || arr[i][0] != '\'')
				lst->content = ft_strjoin(lst->content, arr[i]);
		}
		else
		ft_lstadd_back(&lst, ft_lstnew(arr[i++]));
	}
	












	while (lst)
	{
		printf("|%s|\n", lst->content);
		lst = lst->link;
	}
	

}

// char	*ft_strjoin_c(char *s1, char c)
// {
// 	char	*str;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	if (!s1)
// 		s1 = ft_strdup("");
// 	if (!c)
// 		return (NULL);
// 	str = malloc((ft_strlen(s1) + 2) * sizeof(char));
// 	if (!str)
// 		return (NULL);
// 	while (s1[i])
// 	{
// 		str[i] = s1[i];
// 		i++;
// 	}
// 	str[i] = c;
// 	str[++i] = '\0';
// 	// free(s1);
// 	return (str);
// }
