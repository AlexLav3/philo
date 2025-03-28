/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:25:43 by elavrich          #+#    #+#             */
/*   Updated: 2025/03/28 22:08:49 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		i = -1;
		while (++i < data->total)
		{
			if (check_dead(data, i))
				return (NULL);
			if (data->max_m > 0)
				if (check_all_full(data, i))
					return (NULL);
		}
	}
	return (NULL);
}

void	update_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_m);
	philo->last_meal = get_time(philo->data);
	if (philo->data->max_m > 0 && ++philo->meals == philo->data->max_m)
	{
		philo->v_full = 1;
		printf("philo %d is full\n", philo->id_phil);
	}
	pthread_mutex_unlock(&philo->last_m);
}

int	check_dead(t_data *data, int i)
{
	long int	time_l_m;

	if (pthread_mutex_lock(&data->philos[i].last_m))
		return (0);
	time_l_m = get_time(data) - data->philos[i].last_meal;
	pthread_mutex_unlock(&data->philos[i].last_m);
	if (time_l_m > data->die_time)
	{
		if (pthread_mutex_lock(&data->m_end) != 0)
			return (0);
		data->end = 1;
		pthread_mutex_unlock(&data->m_end);
		printf("%ld, philo %d died\n", get_time(data), data->philos->id_phil);
		return (1);
	}
	return (0);
}

int	check_all_full(t_data *data, int i)
{
	if (pthread_mutex_lock(&data->philos[i].last_m))
		return (0);
	if (data->philos[i].v_full == 1 && data->philos[i].counted == 0)
	{
		data->full_count++;
		data->philos[i].counted = 1;
	}
	if (data->full_count == data->total)
	{
		if (pthread_mutex_lock(&data->m_end))
			return (0);
		data->end = 1;
		pthread_mutex_unlock(&data->philos[i].last_m);
		pthread_mutex_unlock(&data->m_end);
		return (1);
	}
	pthread_mutex_unlock(&data->philos[i].last_m);
	return (0);
}
