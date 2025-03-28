/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 04:17:11 by elavrich          #+#    #+#             */
/*   Updated: 2025/03/28 17:25:54 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

int	space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	result;

	sign = 1;
	i = 0;
	result = 0;
	while (space(nptr[i]))
		++i;
	if (nptr[i] == '-')
	{
		sign *= -1;
		++i;
	}
	else if (nptr[i] == '+')
	{
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + nptr[i] - '0';
		++i;
	}
	++i;
	return (result * sign);
}

int	is_numeric(char **argv, int i, int j)
{
	int	num;

	num = 0;
	while (argv[j])
	{
		while (argv[j][i])
		{
			if (argv[j][i] < '0' || argv[j][i] > '9')
				return (0);
			if (num > INT_MAX / 10 || (num == INT_MAX / 10 && (argv[j][i]
					- '0') > INT_MAX % 10))
				return (0);
			num = num * 10 + (argv[j][i] - '0');
			i++;
		}
		num = 0;
		i = 0;
		j++;
	}
	return (1);
}
