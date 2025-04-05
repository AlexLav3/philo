/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:32:16 by elavrich          #+#    #+#             */
/*   Updated: 2025/04/05 13:43:49 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->start)
	{
		if (philo->id_phil % 2 != 0)
			set_state(philo, IDLE);
		while (1)
		{
			if (check_end(philo))
				break ;
			else if (pick_forks(philo))
			{
				if (!set_state(philo, EAT))
					return (NULL);
				update_last_meal(philo);
				ft_usleep(philo->data->eat_time, philo->data);
				drop_forks(philo);
			}
			set_state(philo, SLEEP);
			ft_usleep(philo->data->sleep_time, philo->data);
			set_state(philo, THINK);
		}
	}
	return (NULL);
}

int	pick_forks(t_philo *philo)
{
	if(check_end(philo))
		return (0);
	else if (pthread_mutex_lock(philo->left_f) == 0)
	{
		set_state(philo, FORK);
		if (pthread_mutex_lock(philo->right_f) == 0)
		{
			set_state(philo, FORK);
			return (1);
		}
		pthread_mutex_unlock(philo->left_f);
	}
	return (0);
}

int	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_f);
	pthread_mutex_unlock(philo->right_f);
	return (0);
}

int	check_end(t_philo *philo)
{
	int	end;

	pthread_mutex_lock(&philo->data->m_end);
	end = philo->data->end;
	pthread_mutex_unlock(&philo->data->m_end);
	return (end);
}
