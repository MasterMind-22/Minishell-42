/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonadry <yonadry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:31:57 by moudrib           #+#    #+#             */
/*   Updated: 2023/05/12 13:44:32 by yonadry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft(t_list *stack)
{
	t_list	*tmp;

	tmp = stack;
	printf("\n                 \e[1m\e[93mList");
	printf("\n---------------------------------------\n");
	printf("|   Token          |           Type   |\n");
	printf("---------------------------------------\n");
	while (tmp)
	{
		printf("|%18s|%18s|\n", tmp->content, tmp->type);
		tmp = tmp->link;
	}
	printf("---------------------------------------\x1B[0m\n\n");
}

t_env	*ft_builtins(char *input, char **env/*, t_list *list*/)
{
	t_env	*envr;

	envr = ft_split_environment(env);
	env_parsing(input, envr);
	// export_parsing(input);

	return (envr);
}

void index_list(t_list **list)
{
	t_list *tmp;
	int		count;

	tmp = *list;
	count = 1;
	while (tmp)
	{
		tmp->pos = count;
		count++;
		tmp = tmp->link;
	}
}

void expand_var(t_list **list, t_env *envr)
{
	t_list *tmp = *list;
	t_env *tmp1 = envr;
	t_vars v;
	v.i = 0;
	index_list(&tmp);
	while (tmp)
	{
		if (tmp->content[0] == '$' && ((tmp->link && is_space(tmp->link->content[0]))
				|| !tmp->link))
		{
			delete_node(list, tmp->pos);
			delete_node(list, tmp->prev->pos);
			delete_node(list, tmp->pos);
		}
		else if (tmp->content[0] == '$' && tmp->link)
		{
			tmp = tmp->link;
			while (ft_isalpha(tmp->content[v.i]) ||
				check_char("0123456789", tmp->content[v.i]))
				v.i++;
			v.str = ft_substr(tmp->content, 0, v.i);
			tmp1 = envr;
			while (tmp1)
			{
				if (!ft_strcmp(tmp1->key, v.str))
				{
					tmp->prev->content = ft_strdup(tmp1->value);
					tmp->prev->content = ft_strjoin(tmp->prev->content ,ft_strdup(&tmp->content[v.i]));
					delete_node(list, tmp->pos);
				}
				tmp1 = tmp1->link;
			}
		}
				
		tmp = tmp->link;
	}
}

t_list	*minihell(char *input)
{
	t_list	*lst;

	lst = ft_split_input(input);
	if (check_syntax(lst))
		return (0);
	lexer(&lst);
	if (ft_strlen(input) && (export_parsing(input) || check_before_value(&lst)))
		return (0);
	return (lst);
}


int	main(int ac, char **av, char **env)
{
	char	*input;
	t_env	*envr;
	t_list	*lst;

	(void)av;
	(void)env;
	if (ac != 1)
		return (0);
	while (1)
	{
		input = readline("➜  Minishell ");
		if (!input)
			break ;
		if (ft_strlen(input))
			add_history(input);
		lst = minihell(input);
		if (lst)
		{
			// remove_unnecessary_nodes(&lst);
			envr = ft_builtins(input, env);
			expand_var(&lst, envr);
			lexer(&lst);
			ft(lst);
			ft_destroy_list(&lst);
		}
		ft_destroy_list_env(&envr);
		free(input);
	}
	return (0);
}
