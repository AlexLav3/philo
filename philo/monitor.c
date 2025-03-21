/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:25:43 by elavrich          #+#    #+#             */
/*   Updated: 2025/03/21 22:01:49 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;

	i = -1;
	data = (t_data *)arg;
	while (1)
	{
		i = -1;
		if (pthread_mutex_lock(&data->m_end) == 0)
		{
			if (data->end == 1)
			{
				pthread_mutex_unlock(&data->m_end);
				return (NULL);
			}
			pthread_mutex_unlock(&data->m_end);
		}
		while (++i < data->total)
		{
			check_dead(data, i);
			if (data->max_m > 0)
				check_all_full(data, i);
		}
	}
	return (NULL);
}

void	update_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_m);
	philo->last_meal = get_time(philo->data);
	philo->meals++;
	if (philo->data->max_m > 0 && philo->meals == philo->data->max_m)
	{
		philo->v_full = 1;
		printf("philo %d is full\n", philo->id_phil);
	}
	pthread_mutex_unlock(&philo->last_m);
}

void	check_dead(t_data *data, int i)
{
	long int	time_l_m;

	if (pthread_mutex_lock(&data->m_end) == 0)
	{
		if (data->end)
		{
			pthread_mutex_unlock(&data->m_end);
			return ;
		}
		if (pthread_mutex_lock(&data->philos[i].last_m) == 0)
		{
			time_l_m = get_time(data) - data->philos[i].last_meal;
			if (time_l_m > data->die_time)
			{
				data->end = 1;
				printf("%ld, philo %d died\n", get_time(data),
					data->philos->id_phil);
			}
			pthread_mutex_unlock(&data->philos[i].last_m);
		}
		pthread_mutex_unlock(&data->m_end);
	}
}

int	check_all_full(t_data *data, int i)
{
	if (pthread_mutex_lock(&data->m_end) == 0)
	{
		if (data->end)
		{
			pthread_mutex_unlock(&data->m_end);
			return (0);
		}
		if (pthread_mutex_lock(&data->philos[i].last_m) == 0)
		{
			if (data->philos[i].v_full == 1 && data->philos[i].counted == 0)
			{
				data->full_count++;
				data->philos[i].counted = 1;
			}
			if (data->full_count == data->total)
				data->end = 1;
			pthread_mutex_unlock(&data->philos[i].last_m);
		}
		pthread_mutex_unlock(&data->m_end);
	}
	return (0);
}
