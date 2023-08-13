/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfernand <sfernand@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 23:56:05 by sfernand          #+#    #+#             */
/*   Updated: 2023/08/11 17:39:15 by sfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	ft_exit(char *str)
{
	ft_putstr_fd("Error : ", 2);
	ft_putstr_fd(str, 2);
	return (0);
}

int	check_death2(t_p *p)
{
	pthread_mutex_lock(&p->arg.dead);
	if (p->arg.stop)
	{
		pthread_mutex_unlock(&p->arg.dead);
		return (1);
	}
	pthread_mutex_unlock(&p->arg.dead);
	return (0);
}

void	stop(t_p *p)
{
	int	i;

	i = -1;
	while (!check_death2(p))
		ft_usleep(1);
	while (++i < p->arg.total)
		pthread_join(p->ph[i].thread_id, NULL);
	pthread_mutex_destroy(&p->arg.write_mutex);
	i = -1;
	while (++i < p->arg.total)
		pthread_mutex_destroy(&p->ph[i].l_f);
	if (p->arg.stop == 2)
		printf("Each philosopher ate %d time(s)\n", p->arg.m_eat);
	free(p->ph);
}

int	main(int argc, char **argv)
{
	t_p		p;

	if (!(parse_args(argc, argv, &p)))
		return (ft_exit("Invalid Arguments\n"));
	p.ph = malloc(sizeof(t_philo) * p.arg.total);
	if (!p.ph)
		return (ft_exit("Malloc returned NULL\n"));
	if (!initialize(&p) || !threading(&p))
	{
		free(p.ph);
		return (0);
	}
	stop(&p);
}
