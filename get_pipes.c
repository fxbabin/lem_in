/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 13:33:11 by arobion           #+#    #+#             */
/*   Updated: 2018/01/22 19:33:00 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_verif_pipe_format(char *line)
{
	int		i;
	int		nb_sep;

	i = 0;
	nb_sep = 0;
	while (line[i] != '\0')
	{
		if (!(ft_isprint(line[i])) || line[i] == ' ')
			return (0);
		if (line[i] == '-')
			nb_sep++;
		i++;
	}
	if (nb_sep != 1)
		return (0);
	return (1);
}

void	ft_launch_pushback(t_room *crawler, char *name)
{
	ft_lstpushback(&(crawler->pipes), init_room(name, 0, 0), 0);
}

int		ft_verif_unicity_of_pipe(t_room *crawler, char *name)
{
	t_list *tmp;

	tmp = crawler->pipes;
	while (tmp)
	{
		if (ft_strcmp(tmp->content, name) == 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int		ft_add_pipes_to_room(t_list **t, char *name1, char *name2)
{
	t_list	*crawler;

	crawler = *t;
	while (crawler)
	{
		if (ft_launch_cmp(crawler->content, name1) == 0)
		{
			if (ft_verif_unicity_of_pipe(crawler->content, name2) == 0)
				return (0);
			ft_launch_pushback(crawler->content, name2);
		}
		if (ft_launch_cmp(crawler->content, name2) == 0)
			ft_launch_pushback(crawler->content, name1);
		crawler = crawler->next;
	}
	return (1);
}

int		ft_search_rooms_name(char *name1, char *name2, t_list **t)
{
	int		i;
	int		j;
	t_list	*crawler;

	if (ft_strcmp(name1, name2) == 0)
		return (0);
	i = 0;
	j = 0;
	crawler = *t;
	while (crawler)
	{
		if (ft_launch_cmp(crawler->content, name1) == 0)
			i = 1;
		crawler = crawler->next;
	}
	crawler = *t;
	while (crawler)
	{
		if (ft_launch_cmp(crawler->content, name2) == 0)
			j = 1;
		crawler = crawler->next;
	}
	if (i == 1 && j == 1)
	{
		if (!(ft_add_pipes_to_room(t, name1, name2)))
			return (0);
		return (1);
	}
	return (0);
}

int		ft_are_rooms_exists(char *line, int i, t_list **t)
{
	int		j;
	char	*name1;
	char	*name2;

	j = 0;
	if (!(name1 = (char*)malloc(sizeof(char) * (i + 1))))
		return (0);
	ft_bzero(name1, i + 1);
	//ft_printf("line i = %s || i = %d\n", line, i);
	while (j < i)
	{
		name1[j] = line[j];
		j++;
	}
	//ft_printf("j = %d\n", j);
	name1[i] = '\0';
//	ft_printf("name1 = %s\n", name1);
	j = i + 1;
	while (line[j] != '\0')
		j++;
	if (!(name2 = (char*)malloc(sizeof(char) * (j - i))))
		return (0);
	j = 0;
	i++;
	while (line[i] != '\0')
	{
		name2[j] = line[i];
		j++;
		i++;
	}
	name2[j] = '\0';
	if (!(ft_search_rooms_name(name1, name2, t)))
	{
		ft_lstndump(t);
		free(name1);
		free(name2);
		return (0);
	}
	free(name1);
	free(name2);
	return (1);
}

int		get_pipes(char *line, t_list **t)
{
	int		i;

	i = 0;
	if (!(ft_verif_pipe_format(line)))
		return (0);
	while (line[i] != '-')
		i++;
	if (!(ft_are_rooms_exists(line, i, t)))
		return (0);
	free(line);
	while (get_next_line(0, &line) > 0)
	{
		i = 0;
		if (ft_verif_line_is_comm(line) == 1)
			continue ;
		if (!(ft_verif_pipe_format(line)))
		{
			free(line);
			return (0);
		}
		while (line[i] != '-')
			i++;
		if (!(ft_are_rooms_exists(line, i, t)))
		{
			free(line);
			return (0);
		}
		ft_printf("line = %s\n", line);
		free(line);
	}
	free(line);
	return (1);
}