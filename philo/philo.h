/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboustaj <hboustaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:03:46 by hboustaj          #+#    #+#             */
/*   Updated: 2024/08/23 15:53:36 by hboustaj         ###   ########.fr       */
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

typedef enum s_status
{
    FORK,
    EATING,
    SLEEPING,
    THINKING,
    DIED
} t_status;

typedef struct s_main t_main;
typedef struct s_forks t_forks;

typedef struct s_philo
{
    int id;
    int meals_count;
    long last_meal_time; 
    t_main *data;
    t_forks *left_fork;
    t_forks *right_fork;
    pthread_t thread;
    pthread_mutex_t p_mutex; 
} t_philo;

struct s_forks
{
    pthread_mutex_t fork;
    int fork_id;
};

struct s_main
{
    int philo_nb;
    int time_die;
    int time_eat;
    int time_slp;
    int max_meals;
    long start_time;
    int death_flag;
    t_philo *philo;
    t_forks *forks;
    pthread_t observer;
    pthread_mutex_t mutex;
    pthread_mutex_t message;
};

void    check_args(int ac, char **av, t_main *data);
void    invalid_input(int ac, char **av);
int     ft_atoi(const char	*str);

void    ft_init(t_main *data);
void    init_philos(t_main *data);
void    init_forks(t_forks *fork, t_philo *philo, int i);

void    start_feeding(t_main *data);
void    *get_dinner(void *p);
void    eating(t_philo *philo);

long    time_now();
void    ft_usleep(long u_time, t_main *data);
void    write_message(t_philo *philo, t_status stat);
int     get_value(pthread_mutex_t *mutex, int *var);
void    incrementer(pthread_mutex_t *mutex, int *var);
void    ft_exit(char *s);
void    turn_the_flag(t_philo *philo, int time);
int    time_out(t_philo *philo);
void    *monitor(void *p);

#endif