/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfernand <sfernand@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 18:36:14 by sfernand          #+#    #+#             */
/*   Updated: 2023/08/15 00:04:16 by sfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	write_status(char *str, t_philo *philo)
{
	long int		time;

	time = -1;
	time = actual_time() - philo->pa->start_t;
	if (time >= 0 && time <= 2147483647 && !check_death(philo, 0))
	{
		printf("%ld ", time);
		printf("Philo %d %s", philo->id, str);
	}
}

void	sleep_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->pa->write_mutex);
	write_status("is sleeping\n", philo);
	pthread_mutex_unlock(&philo->pa->write_mutex);
	ft_usleep(philo->pa->sleep);
	pthread_mutex_lock(&philo->pa->write_mutex);
	write_status("is thinking\n", philo);
	pthread_mutex_unlock(&philo->pa->write_mutex);
	ft_usleep(1);
}

void	activity(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_f);
	pthread_mutex_lock(&philo->pa->write_mutex);
	write_status("has taken a fork\n", philo);
	pthread_mutex_unlock(&philo->pa->write_mutex);
	if (!philo->r_f)
	{
		ft_usleep(philo->pa->die * 2);
		return ;
	}
	pthread_mutex_lock(philo->r_f);
	pthread_mutex_lock(&philo->pa->write_mutex);
	write_status("has taken a fork\n", philo);
	pthread_mutex_unlock(&philo->pa->write_mutex);
	pthread_mutex_lock(&philo->pa->write_mutex);
	write_status("is eating\n", philo);
	pthread_mutex_lock(&philo->pa->time_eat);
	philo->ms_eat = actual_time();
	pthread_mutex_unlock(&philo->pa->time_eat);
	pthread_mutex_unlock(&philo->pa->write_mutex);
	ft_usleep(philo->pa->eat);
	pthread_mutex_unlock(philo->r_f);
	pthread_mutex_unlock(&philo->l_f);
	sleep_think(philo);
}
