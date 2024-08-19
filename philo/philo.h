/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackstar <blackstar@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:46:37 by hboustaj          #+#    #+#             */
/*   Updated: 2024/08/19 15:12:23 by blackstar        ###   ########.fr       */
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

typedef struct s_info t_info;
typedef struct s_forks t_forks;

typedef struct s_philo
{
    int id;
    int meals_count;
    int last_meal_time;
    int full;
    t_info *data;
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

struct s_info
{
    int philo_nb;
    int time_die;
    int time_eat;
    int time_slp;
    int max_meals;
    long start_time;
    int end_time;
    int threads_count;
    int threads_var;
    t_philo *philo;
    t_forks *forks;
    pthread_t is_dead;
    pthread_mutex_t mutex;
    pthread_mutex_t message;
};

void    invalid_input(int ac, char **av);
void    check_args(int ac, char **av, t_info *data);
int     ft_atoi(const char	*str);
void    ft_init(t_info *data);
void    init_philos(t_info *data);
void    init_forks(t_forks *fork, t_philo *philo, int i);
void    ft_exit(char *s);
void    set_value(pthread_mutex_t *mutex, int *var, int val);
void    value_modifier(pthread_mutex_t *mutex, int *var);
int     get_value(pthread_mutex_t *mutex, int *var);
long    time_now();
bool    threadsflag_control(pthread_mutex_t *mutex, int philo_nb, int *threads);
void    *get_dinner(void *p);
int     time_out(t_philo *philo);
void    start_feeding(t_info *data);
void    check_threads(t_info *data);
void    ft_usleep(long u_time, t_info *data);
void    write_message(t_philo *philo, char c);
void    *is_philo_dead(void *p);
void    *one_philo(void *p);

#endif