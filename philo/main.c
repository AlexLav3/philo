/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 01:40:00 by elavrich          #+#    #+#             */
/*   Updated: 2025/03/21 22:04:59 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//-fsanitize=thread
// setarch $(uname -m) -R $SHELL
int	main(int argc, char **argv)
{
	t_data	data;

	if ((argc == 5 || argc == 6) && is_numeric(argv, 0, 1))
	{
		input(argc, argv, &data);
		if (data.total <= 0)
		{
			printf("Wrong input\n");
			return (0);
		}
		full_init(&data);
		start_sim(&data);
		clean_all(&data);
	}
	else
		printf("Wrong input\n");
	return (0);
}
