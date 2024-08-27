/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboustaj <hboustaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:03:46 by hboustaj          #+#    #+#             */
/*   Updated: 2024/08/27 17:27:53 by hboustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <string.h>

typedef enum s_status
{
	FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED
}	t_status;

typedef struct s_main	t_main;
typedef struct s_forks	t_forks;

typedef struct s_philo
{
	pthread_mutex_t		p_mutex;
	pthread_t			thread;
	t_forks				*left_fork;
	t_forks				*right_fork;
	t_main				*data;
	long				last_meal_time;
	int					id;
	int					meals_count;
}	t_philo;

struct s_forks
{
	pthread_mutex_t		fork;
	int					fork_id;
};

struct s_main
{
	pthread_mutex_t		message;
	pthread_mutex_t		mutex;
	pthread_mutex_t		monitor_mtx;
	pthread_mutex_t		monitor_time;
	pthread_t			observer;
	t_philo				*philo;
	t_forks				*forks;
	long				start_time;
	int					philo_nb;
	int					time_die;
	int					time_eat;
	int					time_slp;
	int					max_meals;
	int					full;
	int					death_flag;
	int					all_are_full;
	int					threads_counter;
};

// in parsing.c file
void	check_args(int ac, char **av, t_main *data);
void	invalid_input(int ac, char **av);
int		ft_atoi(const char	*str);

// in ft_init.c file
void	ft_init(t_main *data);
void	init_philos(t_main *data);
void	init_forks(t_forks *fork, t_philo *philo, int i);

// in feeding.c file
void	write_message(t_philo *philo, t_status stat);
void	eating(t_philo *philo);
void	*get_dinner(void *p);
void	start_feeding(t_main *data);

// in utils.c file
void	incrementer(pthread_mutex_t *mutex, int *var);
int		get_value(pthread_mutex_t *mutex, int *var);
void	ft_usleep(long u_time);
long	time_now(void);
long	time_out(t_philo *philo);

// in philo.c file
void	set_value(pthread_mutex_t *mutex, int *var, int val);
bool	turn_and_check(t_philo *philo, long time);
void	*monitor(void *p);

// in ft_error.c file
void	ft_free(t_main *data);
void	ft_exit(char *s);

#endif
