/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboustaj <hboustaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:03:46 by hboustaj          #+#    #+#             */
/*   Updated: 2024/08/26 12:04:23 by hboustaj         ###   ########.fr       */
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
    int full;
    int death_flag;
    t_philo *philo;
    t_forks *forks;
    pthread_t observer;
    pthread_mutex_t monitor_mtx;
    pthread_mutex_t monitor_time;
    pthread_mutex_t mutex;
    pthread_mutex_t message;
};

// in parsing.c file
void    check_args(int ac, char **av, t_main *data);
void    invalid_input(int ac, char **av);
int     ft_atoi(const char	*str);

// in ft_init.c file
void    ft_init(t_main *data);
void    init_philos(t_main *data);
void    init_forks(t_forks *fork, t_philo *philo, int i);

// in feeding.c file
void    write_message(t_philo *philo, t_status stat);
void    eating(t_philo *philo);
void    start_feeding(t_main *data);
void    *get_dinner(void *p);

// in utils.c file
void    incrementer(pthread_mutex_t *mutex, int *var);
int     get_value(pthread_mutex_t *mutex, int *var);
void    ft_usleep(long u_time);
long    time_now();
int     time_out(t_philo *philo);

void    ft_exit(char *s);
void    ft_free(t_main *data, int flag);
void    turn_and_check(t_philo *philo, int time);
void    *monitor(void *p);


#endif