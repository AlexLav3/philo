/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:33:05 by elavrich          #+#    #+#             */
/*   Updated: 2025/03/21 22:05:30 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_state(t_philo *philo, int state)
{
	if (!philo || !philo->data || check_end(philo))
		return ;
	write_stat(philo, state);
}

int	get_state(t_philo *philo)
{
	int	state;

	state = 0;
	if (pthread_mutex_lock(&philo->m_state) == 0)
	{
		philo->state = philo->state;
		pthread_mutex_unlock(&philo->m_state);
	}
	return (state);
}

void	start_sim(t_data *data)
{
	int	i;

	i = 0;
	data->start = 1;
	while (i < data->total)
	{
		pthread_create(&data->philos[i].philos_thread, NULL, routine,
			&data->philos[i]);
		i++;
	}
	pthread_create(&data->monitor, NULL, monitor, (void *)data);
	pthread_join(data->monitor, NULL);
	i = 0;
	while (i < data->total)
	{
		pthread_join(data->philos[i].philos_thread, NULL);
		i++;
	}
}

void	write_stat(t_philo *philo, int state)
{
	if (pthread_mutex_lock(&philo->m_state) == 0)
	{
		philo->state = state;
		if (state == EAT)
			printf("%ld, philo %d is eating\n", get_time(philo->data),
				philo->id_phil);
		else if (state == SLEEP)
			printf("%ld, philo %d is sleeping\n", get_time(philo->data),
				philo->id_phil);
		else if (state == THINK)
			printf("%ld, philo %d is thinking\n", get_time(philo->data),
				philo->id_phil);
		pthread_mutex_unlock(&philo->m_state);
	}
}
