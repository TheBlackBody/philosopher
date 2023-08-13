/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfernand <sfernand@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 00:25:58 by sfernand          #+#    #+#             */
/*   Updated: 2023/08/11 17:36:58 by sfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	*is_dead(void	*data)
{
	t_philo					*philo;

	philo = (t_philo *)data;
	ft_usleep(philo->pa->die + 1);
	pthread_mutex_lock(&philo->pa->time_eat);
	pthread_mutex_lock(&philo->pa->finish);
	if (!check_death(philo, 0) && !philo->finish && ((actual_time() - philo->ms_eat) \
		>= (long)(philo->pa->die)))
	{
		pthread_mutex_unlock(&philo->pa->time_eat);
		pthread_mutex_unlock(&philo->pa->finish);
		pthread_mutex_lock(&philo->pa->write_mutex);
		write_status("died\n", philo);
		pthread_mutex_unlock(&philo->pa->write_mutex);
		check_death(philo, 1);
	}
	pthread_mutex_unlock(&philo->pa->time_eat);
	pthread_mutex_unlock(&philo->pa->finish);
	return (NULL);
}

void	*thread(void *data)
{
	t_philo					*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		ft_usleep(philo->pa->eat / 10);
	while (!check_death(philo, 0))
	{
		pthread_create(&philo->thread_death_id, NULL, is_dead, data);
		activity(philo);
		pthread_detach(philo->thread_death_id);
		if ((int)++philo->nb_eat == philo->pa->m_eat)
		{
			pthread_mutex_lock(&philo->pa->finish);
			philo->finish = 1;
			philo->pa->nb_p_finish++;
			if (philo->pa->nb_p_finish == philo->pa->total)
			{
				pthread_mutex_unlock(&philo->pa->finish);
				check_death(philo, 2);
			}
			pthread_mutex_unlock(&philo->pa->finish);
			return (NULL);
		}
	}
	return (NULL);
}

int	threading(t_p *p)
{
	int	i;

	i = 0;
	while (i < p->arg.total)
	{
		p->ph[i].pa = &p->arg;
		if (pthread_create(&p->ph[i].thread_id, NULL, thread, &p->ph[i]) != 0)
			return (ft_exit("Pthread did not return 0\n"));
		i++;
	}
	return (1);
}
