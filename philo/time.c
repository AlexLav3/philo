/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 23:22:59 by elavrich          #+#    #+#             */
/*   Updated: 2025/03/21 22:04:19 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	get_time(t_data *data)
{
	struct timeval	current_time;
	long int		time;

	if (gettimeofday(&current_time, NULL) == -1)
		return (0);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	if (data->start_time == 0)
		data->start_time = time;
	return (time - data->start_time);
}

void	ft_usleep(long int sleep_time, t_data *data)
{
	long int	start_time;

	start_time = get_time(data);
	while ((get_time(data) - start_time) < sleep_time)
		usleep(sleep_time / 10);
}
