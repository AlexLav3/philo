/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 00:50:11 by elavrich          #+#    #+#             */
/*   Updated: 2025/03/28 17:19:39 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clean_all(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->m_end);
	while (i < data->total)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	free(data->philos);
}
