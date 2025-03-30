/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:33:05 by elavrich          #+#    #+#             */
/*   Updated: 2025/03/30 21:34:45 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	set_state(t_philo *philo, int state)
{
	if (check_end(philo))
	{
		if (state == EAT)
			drop_forks(philo);
		return (0);
	}
	write_stat(philo, state);
	return (1);
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
		if (pthread_create(&data->philos[i].philos_thread, NULL, routine,
				&data->philos[i]))
			return ;
		i++;
	}
	if (pthread_create(&data->monitor, NULL, monitor, (void *)data))
		return ;
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
	if (pthread_mutex_lock(&philo->m_state))
		return ;
	philo->state = state;
	if (state == EAT)
	{
		printf("%ld, philo %d is eating\n", get_time(philo->data),
			philo->id_phil);
	}
	else if (state == SLEEP)
		printf("%ld, philo %d is sleeping\n", get_time(philo->data),
			philo->id_phil);
	else if (state == THINK)
		printf("%ld, philo %d is thinking\n", get_time(philo->data),
			philo->id_phil);
	else if (state == IDLE)
	{
		printf("%ld, philo %d is thinking\n", get_time(philo->data),
			philo->id_phil);
			ft_usleep(100, philo->data);	
	}
			
	pthread_mutex_unlock(&philo->m_state);
}
