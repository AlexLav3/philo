/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 04:32:13 by elavrich          #+#    #+#             */
/*   Updated: 2025/03/28 17:13:36 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	input(int argc, char **argv, t_data *data)
{
	data->total = ft_atoi(argv[1]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	data->die_time = ft_atoi(argv[2]);
	data->max_m = 0;
	if (argc == 6)
		data->max_m = ft_atoi(argv[5]);
}

void	init_forks(t_philo *philo, t_data *data, int pos)
{
	int	philo_nbr;

	philo_nbr = philo->id_phil;
	if (philo->id_phil % 2 == 0)
	{
		philo->right_f = &data->forks[pos];
		philo->left_f = &data->forks[(pos + 1) % data->total];
	}
	else
	{
		philo->left_f = &data->forks[pos];
		philo->right_f = &data->forks[(pos + 1) % data->total];
	}
}

void	init_mt(t_philo *philo)
{
	pthread_mutex_init(&philo->last_m, NULL);
	pthread_mutex_init(&philo->tot_m, NULL);
	pthread_mutex_init(&philo->m_time, NULL);
	pthread_mutex_init(&philo->m_state, NULL);
}

void	init_philos(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < data->total)
	{
		philo = &data->philos[i];
		philo->data = data;
		philo->id_phil = i + 1;
		philo->v_full = 0;
		philo->meals = 0;
		philo->counted = 0;
		init_mt(philo);
		philo->last_meal = get_time(philo->data);
		philo->state = 5;
		init_forks(philo, data, i);
		i++;
	}
}

void	full_init(t_data *data)
{
	int	i;

	data->end = 0;
	if (data->total == 1)
		data->end = 1;
	data->start = 0;
	data->full_count = 0;
	data->start_time = 0;
	data->philos = malloc(sizeof(t_philo) * data->total);
	if (!data->philos)
		return ;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->total);
	if (!data->forks)
		return ;
	pthread_mutex_init(&data->m_end, NULL);
	i = 0;
	while (i < data->total)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	init_philos(data);
}
