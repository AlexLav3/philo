/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elavrich <elavrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 22:10:09 by elavrich          #+#    #+#             */
/*   Updated: 2025/04/05 13:44:40 by elavrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define EAT 1
# define THINK 2
# define SLEEP 3
# define DEAD 4
# define IDLE 5
# define END 6
# define FORK 7

typedef pthread_mutex_t	t_mx;
typedef struct philo	t_philo;

typedef struct data
{
	int					die_time;
	int					sleep_time;
	int					eat_time;
	int					total;
	int					full_count;
	int					max_m;
	pthread_t			monitor;
	int					start;
	long int			start_time;
	int					end;
	t_mx				m_end;
	t_mx				*n_phil;
	t_mx				*forks;
	t_philo				*philos;
}						t_data;

typedef struct philo
{
	int					id_phil;
	pthread_t			philos_thread;
	int					meals;
	int					v_full;
	long int			last_meal;
	int					state;
	int					counted;
	t_data				*data;
	t_mx				*left_f;
	t_mx				*right_f;
	t_mx				tot_m;
	t_mx				m_time;
	t_mx				last_m;
	t_mx				m_state;
}						t_philo;

int						check_end(t_philo *philo);
void					write_stat(t_philo *philo, int state);

void					update_last_meal(t_philo *philo);
int						check_all_full(t_data *data, int i);
int						check_dead(t_data *data, int i);
void					start_sim(t_data *data);
//time funcions -

void					ft_usleep(long int sleep_time, t_data *data);
long int				get_time(t_data *data);

//init
void					init_mt(t_philo *philo);
void					full_init(t_data *data);
void					init_philos(t_data *data);
void					init_forks(t_philo *philo, t_data *data, int pos);
void					input(int argc, char **argv, t_data *data);

//init monitor
void					*monitor(void *arg);

//routine
void					*routine(void *arg);

//forks
int						pick_forks(t_philo *philo);
int						drop_forks(t_philo *philo);

//set state?
int						set_state(t_philo *philo, int state);
int						get_state(t_philo *philo);
void					die(t_data *data, int i);
void					start_sim(t_data *data);

//cleanup and error functions
void					clean_all(t_data *data);

//utils
int						space(char c);
int						ft_atoi(const char *nptr);
int						is_numeric(char **argv, int i, int j);
int						ft_strlen(char *str);

#endif