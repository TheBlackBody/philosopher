/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfernand <sfernand@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 00:24:19 by sfernand          #+#    #+#             */
/*   Updated: 2023/08/11 16:41:22 by sfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	sum;

	sum = 0;
	i = -1;
	while (str[++i])
		sum = (sum * 10) + (str[i] - 48);
	return (sum);
}

int	numeric(char **argv, int i, int j)
{
	while (argv[j])
	{
		while (argv[j][i])
		{
			if (argv[j][i] < '0' || argv[j][i] > '9' || ft_strlen(argv[j]) > 10)
				return (0);
			i++;
		}
		i = 0;
		j++;
	}
	return (1);
}

int	parse_args(int argc, char **argv, t_p *p)
{
	if ((argc == 5 || argc == 6) && numeric(argv, 0, 1))
	{
		p->arg.total = ft_atoi(argv[1]);
		p->arg.die = ft_atoi(argv[2]);
		p->arg.eat = ft_atoi(argv[3]);
		p->arg.sleep = ft_atoi(argv[4]);
		p->arg .m_eat = -1;
		if (argc == 6)
			p->arg.m_eat = ft_atoi(argv[5]);
		if (p->arg.total <= 0 || p->arg.die <= 0 || p->arg.eat <= 0 \
			|| p->arg.sleep <= 0)
			return (0);
		return (1);
	}
	return (0);
}

void	init_mutex(t_p *p)
{
	pthread_mutex_init(&p->arg.write_mutex, NULL);
	pthread_mutex_init(&p->arg.dead, NULL);
	pthread_mutex_init(&p->arg.time_eat, NULL);
	pthread_mutex_init(&p->arg.finish, NULL);
}

int	initialize(t_p *p)
{
	int	i;

	i = 0;
	p->arg.start_t = actual_time();
	p->arg.stop = 0;
	p->arg.nb_p_finish = 0;
	init_mutex(p);
	while (i < p->arg.total)
	{
		p->ph[i].id = i + 1;
		p->ph[i].ms_eat = p->arg.start_t;
		p->ph[i].nb_eat = 0;
		p->ph[i].finish = 0;
		p->ph[i].r_f = NULL;
		pthread_mutex_init(&p->ph[i].l_f, NULL);
		if (p->arg.total == 1)
			return (1);
		if (i == p->arg.total - 1)
			p->ph[i].r_f = &p->ph[0].l_f;
		else
			p->ph[i].r_f = &p->ph[i + 1].l_f;
		i++;
	}
	return (1);
}
